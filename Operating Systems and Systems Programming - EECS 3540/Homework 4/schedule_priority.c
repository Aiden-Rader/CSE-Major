/**
 * Implementation of various scheduling algorithms.
 *
 * Priority scheduling
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

// pick the task with the highest priority
Task *pickNextTask() {
    struct node *temp = head;
    struct node *highestPriorityNode = head;
    
    while (temp != NULL) {
        if (temp->task->priority > highestPriorityNode->task->priority) {
            highestPriorityNode = temp;
        }
        temp = temp->next;
    }
    return highestPriorityNode->task;
}

// run all tasks in the list in order of priority
void schedule() {
    while (head != NULL) {
        Task *current = pickNextTask();
        run(current, current->burst);
        delete(&head, current);
    }
}
