/**
 * Implementation of various scheduling algorithms.
 *
 * RR scheduling
 */

 #include <stdlib.h>
 #include <stdio.h>
 
 #include "task.h"
 #include "list.h"
 #include "cpu.h"

 #define TIME_QUANTUM 10
 
 // reference to the head of the list
 struct node *head = NULL;
 
 int nextTid = 0;
 
 // add a new task to the list of tasks
void add(char *name, int priority, int burst) {
    Task *newTask = (Task *)malloc(sizeof(Task));

    newTask->name = name;
    newTask->tid = nextTid++;
    newTask->priority = priority;
    newTask->burst = burst;

    insert(&head, newTask);
}

// Round-Robin Scheduler
void schedule() {
    struct node *tempNode = head;

    while (head != NULL) {
        Task *current = tempNode->task;

        int slice = current->burst > TIME_QUANTUM ? TIME_QUANTUM : current->burst;
        run(current, slice);
        current->burst -= slice;

        struct node *next = tempNode->next;

        if (current->burst <= 0) {
            // Task is finished
            delete(&head, current);
            printf("Task %s finished.\n", current->name);
        } else {
            // Move task to the end of the list
            delete(&head, current);
            insert(&head, current);
        }

        // Advance to next node
        tempNode = next;

        // If we reach end of list, start over from head
        if (tempNode == NULL) {
            tempNode = head;
        }
    }
}