// Create a file driver.c that reads in the schedule of tasks, inserts each task into a linked list, and
// invokes the process scheduler by calling the schedule() function.


// The schedule() function executes each task according to the specified scheduling algorithm.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include all mandatory header files
#include "task.h"
#include "list.h"
#include "cpu.h"
#include "scheduler.h"

#define MAX_LINE 100

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <schedule file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        char name[10];
        int priority, burst;

        if (sscanf(line, "%[^,], %d, %d", name, &priority, &burst) == 3) {
            char *taskName = strdup(name);
            add(taskName, priority, burst);
        }
    }

    fclose(file);
    
    schedule();
    return 0;
}