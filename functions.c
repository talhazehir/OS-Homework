#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int parse_input_file(const char *filename, Process processes[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening input file.\n");
        return -1;
    }

    int i = 0;
    while (fscanf(file, " %[^,], %d, %d, %d, %d, %d",
                  processes[i].process_number,
                  &processes[i].arrival_time,
                  &processes[i].priority,
                  &processes[i].burst_time,
                  &processes[i].ram,
                  &processes[i].cpu) != EOF) {
        i++;
    }

    fclose(file);
    return i;
}

void assign_to_cpu1(Process processes[], int num_processes, Process cpu1_queue[], int *cpu1_queue_size) {
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].priority == 0) {
            cpu1_queue[*cpu1_queue_size] = processes[i];
            (*cpu1_queue_size)++;
        }
    }
}

void assign_to_cpu2(Process processes[], int num_processes, Process cpu2_queues[NUM_PRIORITY_LEVELS][MAX_PROCESSES], int cpu2_queue_sizes[NUM_PRIORITY_LEVELS]) {
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].priority > 0) {
            int priority_index = processes[i].priority - 1;
            cpu2_queues[priority_index][cpu2_queue_sizes[priority_index]] = processes[i];
            cpu2_queue_sizes[priority_index]++;
        }
    }
}
