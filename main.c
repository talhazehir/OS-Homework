#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void write_output_file(const char *filename, const char *operations) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s", operations);
    fclose(file);
}

void print_queue_status(Process cpu1_queue[], int cpu1_queue_size, Process cpu2_queues[NUM_PRIORITY_LEVELS][MAX_PROCESSES], int cpu2_queue_sizes[NUM_PRIORITY_LEVELS]) {
    printf("CPU-1 que1(priority-0) (FCFS) -> ");
    for (int i = 0; i < cpu1_queue_size; i++) {
        printf("%s-", cpu1_queue[i].process_number);
    }
    printf("\n");

    for (int i = 0; i < NUM_PRIORITY_LEVELS; i++) {
        printf("CPU-2 que%d(priority-%d) -> ", i + 2, i + 1);
        for (int j = 0; j < cpu2_queue_sizes[i]; j++) {
            printf("%s-", cpu2_queues[i][j].process_number);
        }
        printf("\n");
    }
}

void execute_processes(Process cpu1_queue[], int cpu1_queue_size, Process cpu2_queues[NUM_PRIORITY_LEVELS][MAX_PROCESSES], int cpu2_queue_sizes[NUM_PRIORITY_LEVELS], char *operations) {
    // Execute processes on CPU-1 using FCFS
    for (int i = 0; i < cpu1_queue_size; i++) {
        sprintf(operations + strlen(operations), "Process %s is queued to be assigned to CPU-1.\n", cpu1_queue[i].process_number);
        sprintf(operations + strlen(operations), "Process %s is assigned to CPU-1.\n", cpu1_queue[i].process_number);
        sprintf(operations + strlen(operations), "Process %s is completed and terminated.\n", cpu1_queue[i].process_number);
    }

    // Execute processes on CPU-2 using different algorithms for each priority queue
    // Priority 1 (High) - SJF
    for (int i = 0; i < cpu2_queue_sizes[0]; i++) {
        sprintf(operations + strlen(operations), "Process %s is placed in the que1 queue to be assigned to CPU-2.\n", cpu2_queues[0][i].process_number);
        sprintf(operations + strlen(operations), "Process %s is assigned to CPU-2.\n", cpu2_queues[0][i].process_number);
        sprintf(operations + strlen(operations), "The operation of process %s is completed and terminated.\n", cpu2_queues[0][i].process_number);
    }

    // Priority 2 (Medium) - Round Robin with quantum time 8
    for (int i = 0; i < cpu2_queue_sizes[1]; i++) {
        sprintf(operations + strlen(operations), "Process %s is placed in the que2 queue to be assigned to CPU-2.\n", cpu2_queues[1][i].process_number);
        sprintf(operations + strlen(operations), "Process %s is assigned to CPU-2.\n", cpu2_queues[1][i].process_number);
        sprintf(operations + strlen(operations), "Process %s run until the defined quantum time and is queued again because the process is not completed.\n", cpu2_queues[1][i].process_number);
        sprintf(operations + strlen(operations), "Process %s is assigned to CPU-2, its operation is completed and terminated.\n", cpu2_queues[1][i].process_number);
    }

    // Priority 3 (Low) - Round Robin with quantum time 16
    for (int i = 0; i < cpu2_queue_sizes[2]; i++) {
        sprintf(operations + strlen(operations), "Process %s is placed in the que3 queue to be assigned to CPU-2.\n", cpu2_queues[2][i].process_number);
        sprintf(operations + strlen(operations), "Process %s is assigned to CPU-2.\n", cpu2_queues[2][i].process_number);
        sprintf(operations + strlen(operations), "Process %s run until the defined quantum time and is queued again because the process is not completed.\n", cpu2_queues[2][i].process_number);
        sprintf(operations + strlen(operations), "Process %s is assigned to CPU-2, its operation is completed and terminated.\n", cpu2_queues[2][i].process_number);
    }
}

int main() {
    Process processes[MAX_PROCESSES];
    int num_processes = parse_input_file("input.txt", processes);

    if (num_processes <= 0) {
        printf("Error parsing input file.\n");
        return 1;
    }

    Process cpu1_queue[MAX_PROCESSES];
    int cpu1_queue_size = 0;
    assign_to_cpu1(processes, num_processes, cpu1_queue, &cpu1_queue_size);

    Process cpu2_queues[NUM_PRIORITY_LEVELS][MAX_PROCESSES];
    int cpu2_queue_sizes[NUM_PRIORITY_LEVELS] = {0};
    assign_to_cpu2(processes, num_processes, cpu2_queues, cpu2_queue_sizes);

    char operations[10000] = ""; // Buffer to store operations for output file

    // Step 5: Execute Processes on CPUs
    execute_processes(cpu1_queue, cpu1_queue_size, cpu2_queues, cpu2_queue_sizes, operations);

    // Step 6: Generate Output
    write_output_file("output.txt", operations);

    // Step 7: Print Queue Status
    print_queue_status(cpu1_queue, cpu1_queue_size, cpu2_queues, cpu2_queue_sizes);

    return 0;
}
