#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define MAX_PROCESSES 100
#define NUM_PRIORITY_LEVELS 3

typedef struct {
    char process_number[10];
    int arrival_time;
    int priority;
    int burst_time;
    int ram;
    int cpu;
} Process;

int parse_input_file(const char *filename, Process processes[]);
void assign_to_cpu1(Process processes[], int num_processes, Process cpu1_queue[], int *cpu1_queue_size);
void assign_to_cpu2(Process processes[], int num_processes, Process cpu2_queues[NUM_PRIORITY_LEVELS][MAX_PROCESSES], int cpu2_queue_sizes[NUM_PRIORITY_LEVELS]);

#endif
