// Librerias.
#include <stdio.h> // Para printf.
#include <unistd.h> // Para manejar la repetición cada 2 seg.
#include <ncurses.h> // Manejo de interfaz de texto (TUI).

// Para obetener los datos de la CPU y Memoria.
#include "cpu.h"
#include "mem.h"


int main() {
    char cpu_model[MAX_LINE] = ""; // Recibe el nombre (modelo) del procesador.
    int cores; // Recibe el número de núcleos, utilizaremos & para que se sobreescriba en la función (puntero).
    get_cpu_info(cpu_model, sizeof(cpu_model), &cores); // Función de cpu.c para obtener los datos de cpuinfo.

    CpuStats prev_stats[MAX_CORES], curr_stats[MAX_CORES]; // Recibe las estadisticas de cada núcleo.
    get_cpu_stats(prev_stats, &cores); // Función que actualiza las estadísticas.

    // Ajustamos la interfaz.
    initscr(); // Inicializamos.
    noecho(); // Desactiva el teclado.
    curs_set(FALSE); // Oculta el mouse.

    while (1) {
	// Variables para la memoria ram y swap (extensión de ram en linux).
        long total_mem, used_mem, swap_used;
        get_mem_info(&total_mem, &used_mem, &swap_used); // Obtener datos de memoria.
        get_cpu_stats(curr_stats, &cores); // Obtener datos del procesador.

	// Reescribir en la interfaz la información actualizada.
        clear();
        mvprintw(0, 0, "=== Show System Information ===");
        mvprintw(1, 0, "CPU Model: %s", cpu_model);
        mvprintw(2, 0, "Cores: %d", cores);
        mvprintw(3, 0, "Memory: %ld MB total, %ld MB used", total_mem, used_mem);
        mvprintw(4, 0, "Swap Used: %ld MB", swap_used);
	
	// Muestra información de cada núcleo.
        for (int i = 0; i < cores; i++) {
            double usage = calc_cpu_usage(prev_stats[i], curr_stats[i]);
            mvprintw(6 + i, 0, "Core %d: %.2f%%", i, usage);
            prev_stats[i] = curr_stats[i];
        }

        refresh(); // Actualiza la pantalla.
        sleep(2); // Pausa el bucle 2 segundos.
    }

    // Para cerrar el programa al usar ctrl + c.
    endwin(); // Cierra la pantalla (ncurses).
    return 0;
}
