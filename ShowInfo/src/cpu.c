// Librerias.
#include <stdio.h> // Para manejo de archivos.
#include <string.h> // Para manejo de cadenas strings.
#include "cpu.h" // Define las variables y funciones (cabecera).

// Conseguimos la información general de la cpu.
void get_cpu_info(char *model, size_t size, int *cores) {
    FILE *f = fopen("/proc/cpuinfo", "r"); // Abrimos los datos de la cpu.
    char line[MAX_LINE]; // Leerá cada línea.
    *cores = 0; // Cuenta los núcleos.
    model[0] = '\0'; 

    // Bucle para leer el archivo línea por línea.
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "model name", 10) == 0 && model[0] == '\0') {
            char *colon = strchr(line, ':'); // Busca donde dice "model name".
            if (colon) {
                strncpy(model, colon + 2, size - 1); // Copia el nombre de la cpu (el +2 es para saltar :)
                model[strcspn(model, "\n")] = 0; // Eliminamos salto de línea.
            }
        }
	// Aquí obtenemos el número de núcleos, busca cada vez que diga "processor".
        if (strncmp(line, "processor", 9) == 0) {
            (*cores)++;
        }
    }
    fclose(f); // Cerramos el archivo.
}

// Conseguimos el estado de la cpu.
void get_cpu_stats(CpuStats stats[], int *cores) {
    // Abrimos el archivo y usamos variables auxiliares.
    FILE *f = fopen("/proc/stat", "r");
    char line[MAX_LINE];
    int idx = 0;
    
    // Recorre línea por línea buscando donde diga cpu0, cpu1, ...
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "cpu", 3) == 0 && line[3] != ' ') {
            sscanf(line, "cpu%d %llu %llu %llu %llu %llu %llu %llu %llu",
                   &idx, &stats[idx].user, &stats[idx].nice, &stats[idx].system,
                   &stats[idx].idle, &stats[idx].iowait, &stats[idx].irq,
                   &stats[idx].softirq, &stats[idx].steal);
            idx++; // Pasamos al siguiente núcleo.
        }
    }
    fclose(f); // Cerramos el archivo.
    *cores = idx;
}

// Calculamos los tiempos de cuanto pasó entre la lectura anterior y la actual.
// Esto debido a que los datos de stats son acumulativos desde que se encendío el sistema.
double calc_cpu_usage(CpuStats prev, CpuStats curr) {
    unsigned long long prev_idle = prev.idle + prev.iowait;
    unsigned long long curr_idle = curr.idle + curr.iowait;

    unsigned long long prev_total = prev.user + prev.nice + prev.system +
                                    prev.idle + prev.iowait + prev.irq +
                                    prev.softirq + prev.steal;
    unsigned long long curr_total = curr.user + curr.nice + curr.system +
                                    curr.idle + curr.iowait + curr.irq +
                                    curr.softirq + curr.steal;

    unsigned long long totald = curr_total - prev_total;
    unsigned long long idled = curr_idle - prev_idle;

    return (totald - idled) * 100.0 / totald; // Damos el porcentaje de uso de la cpu.
}
