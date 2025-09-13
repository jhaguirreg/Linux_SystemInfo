#ifndef CPU_H
#define CPU_H

#define MAX_LINE 1024
#define MAX_CORES 128

typedef struct {
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
} CpuStats;

// Funciones de CPU
void get_cpu_info(char *model, size_t size, int *cores);
void get_cpu_stats(CpuStats stats[], int *cores);
double calc_cpu_usage(CpuStats prev, CpuStats curr);

#endif
