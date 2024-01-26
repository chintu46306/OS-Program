
/*
Write a C program to simulate the MVT
and MFT memory management
techniques
*/

#include <stdio.h>

#define MAX_TASKS 10

void MVT(int tasks[], int n, int memory_size) {
    int memory[memory_size];
    int memory_alloc[MAX_TASKS];
    int external_fragmentation = 0;

    for (int i = 0; i < memory_size; i++) {
        memory[i] = -1; // Initialize memory with -1 (empty)
    }

    for (int i = 0; i < n; i++) {
        int task = tasks[i];
        int task_size = memory_alloc[task];
        
        // Check if task is already allocated in memory
        if (task_size > 0) {
            printf("Task %d is already allocated in Memory Slot %d\n", task, task_size);
        } else {
            // Find the first available slot that can accommodate the task
            int slot = -1;
            for (int j = 0; j < memory_size; j++) {
                if (memory[j] == -1) { // Empty slot
                    if (slot == -1 || (j - slot) < (memory_size - task)) {
                        slot = j;
                    }
                }
            }

            if (slot != -1) {
                // Allocate task in the selected slot
                for (int j = 0; j < task; j++) {
                    memory[slot + j] = i; // Set memory slot value as task index
                    memory_alloc[i] = slot; // Update task's allocated slot
                }
                printf("Task %d is allocated in Memory Slot %d\n", i, slot);
            } else {
                printf("Task %d cannot be allocated due to insufficient memory\n", i);
                external_fragmentation += task;
            }
        }
    }

    printf("External Fragmentation: %d\n", external_fragmentation);
}

void MFT(int tasks[], int n, int memory_size, int block_size) {
    int num_blocks = memory_size / block_size;
    int memory[num_blocks];
    int memory_alloc[MAX_TASKS];
    int external_fragmentation = 0;

    for (int i = 0; i < num_blocks; i++) {
        memory[i] = -1; // Initialize memory with -1 (empty)
    }

    for (int i = 0; i < n; i++) {
        int task = tasks[i];
        int task_blocks = (task + block_size - 1) / block_size;
        int task_size = memory_alloc[task];
        
        // Check if task is already allocated in memory
        if (task_size > 0) {
            printf("Task %d is already allocated in Memory Block %d\n", task, task_size);
        } else {
            // Find the first available block that can accommodate the task
            int block = -1;
            for (int j = 0; j < num_blocks; j++) {
                if (memory[j] == -1) { // Empty block
                    int available_blocks = 0;
                    for (int k = j; k < num_blocks && memory[k] == -1; k++) {
                        available_blocks++;
                    }
                    if (available_blocks >= task_blocks) {
                        block = j;
                        break;
                    }
                }
            }

            if (block != -1) {
                // Allocate task in the selected block
                for (int j = 0; j < task_blocks; j++) {
                    memory[block + j] = i; // Set memory block value as task index
                    memory_alloc[i] = block; // Update task's allocated block
                }
                printf("Task %d is allocated in Memory Block %d\n", i, block);
            } else {
                printf("Task %d cannot be allocated due to insufficient memory\n", i);
                external_fragmentation += task;
            }
        }
    }

    printf("External Fragmentation: %d\n", external_fragmentation);
}

int main() {
    int n;
    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    int tasks[MAX_TASKS];
    printf("Enter the memory requirements for each task:\n");
    for (int i = 0; i < n; i++) {
        printf("Task %d: ", i);
        scanf("%d", &tasks[i]);
    }

    int memory_size, block_size;
    printf("Enter the total memory size: ");
    scanf("%d", &memory_size);

    printf("Enter the block size for MFT (0 for MVT): ");
    scanf("%d", &block_size);

    if (block_size > 0) {
        MFT(tasks, n, memory_size, block_size);
    } else {
        MVT(tasks, n, memory_size);
    }

    return 0;
}
