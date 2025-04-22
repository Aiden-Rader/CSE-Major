/**
 * Implementation of various scheduling algorithms.
 *
 * SJF scheduling
 */

#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

// reference to the head of the list
struct node *head = NULL;

int nextTid = 0;

Task *pickNextTask();

// add a new task to the list of tasks
void add(char *name, int priority, int burst) 
{
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));

    // Initialize the new task struct
    newTask->name = name; 
    newTask->tid = nextTid++;
    newTask->priority = priority;
    newTask->burst = burst;

    // insert the new task into the list of tasks 
    insert(&head, newTask);
}

/**
 * Run the FCFS scheduler
 */
void schedule() 
{
    Task *current;

    // While the head is not the current node, pick the task with shortest burst time,
    // run said task and then delete it from the list after its done executing
    while (head != NULL) {

        current = pickNextTask();  // This gets the shortest task and sets it as its current task to exe

        run(current, current->burst);

        delete(&head, current);

    }
}

/**
 * Returns the next task selected to run.
 */
Task *pickNextTask()
{
    // If there is no head, return Null
    if (head == NULL) {
        return NULL;
    }

    // Initialize the nodes and set them to head node
    struct node *tempNode = head;
    struct node *shortestNode = head; // Assume head is the shortest initially

    // While there is stil a temp node availible loop the system
    while (tempNode != NULL) {

        // If the temp node 
        if (tempNode->task->burst < shortestNode->task->burst) {
            shortestNode = tempNode;  // Found a shorter task
        }
        tempNode = tempNode->next;
    }

    return shortestNode->task;  // Return the shortest task
}




