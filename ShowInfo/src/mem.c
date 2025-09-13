// Librerías.
#include <stdio.h> // Para archivos.
#include "mem.h"

// Actualizará con punteros los datos de memoria al main.
void get_mem_info(long *total, long *used, long *swap_used) {
    FILE *f = fopen("/proc/meminfo", "r"); // Abrimos el archivo de infromación de memoria.
    char line[1024]; // Para leer cada línea.
    long mem_total = 0, mem_available = 0, swap_total = 0, swap_free = 0; // Variables auxiliares para el calculo.

    while (fgets(line, sizeof(line), f)) {
	// Buscamos en todo el archivo las líneas que requerimos.
        if (sscanf(line, "MemTotal: %ld kB", &mem_total) == 1) continue;
        if (sscanf(line, "MemAvailable: %ld kB", &mem_available) == 1) continue;
        if (sscanf(line, "SwapTotal: %ld kB", &swap_total) == 1) continue;
        if (sscanf(line, "SwapFree: %ld kB", &swap_free) == 1) continue;
    }
    fclose(f); // Cerramos el archivo.
	
    // Pasamos de KB  a MB y hacemos los calculos de memoria usada.
    *total = mem_total / 1024; // MB
    *used = (mem_total - mem_available) / 1024;
    *swap_used = (swap_total - swap_free) / 1024;
}
