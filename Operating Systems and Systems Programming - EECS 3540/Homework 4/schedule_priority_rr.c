/**
 * Implementation of various scheduling algorithms.
 *
 * Priority Round Robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

#define TIME_QUANTUM 10

struct node *head = NULL;

// Add a new task to the list of tasks
void add(char *name, int priority, int burst) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&head, newTask);
}

// Schedule tasks based on priority and round-robin within each priority level
void schedule() {
    while (head != NULL) {
        struct node *tempNode = head;
        struct node *highestPriorityNode = head;

        // Find the highest priority task
        while (tempNode != NULL) {
            if (tempNode->task->priority > highestPriorityNode->task->priority) {
                highestPriorityNode = tempNode;
            }
            tempNode = tempNode->next;
        }

        int highestPriority = highestPriorityNode->task->priority;

        // Run all tasks at the highest priority level using Round Robin
        tempNode = head;
        while (tempNode != NULL) {
            if (tempNode->task->priority == highestPriority) {
                Task *current = tempNode->task;
                int runTime = (current->burst > TIME_QUANTUM) ? TIME_QUANTUM : current->burst;
                run(current, runTime);
                current->burst -= runTime;

                if (current->burst <= 0) {
                    struct node *next = tempNode->next;
                    delete(&head, current);
                    printf("Task %s finished.\n", current->name);
                    tempNode = next;
                } else {
                    tempNode = tempNode->next;
                }
            } else {
                tempNode = tempNode->next;
            }
        }
    }
}

