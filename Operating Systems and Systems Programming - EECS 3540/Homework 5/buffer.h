// Defining Buffer Size in header file
#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>
#include <semaphore.h>

typedef int buffer_item;
#define BUFFER_SIZE 5

// Blueprint of the functions in buffer.c
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void initialize_buffer(void);

extern sem_t empty;
extern sem_t full;
extern pthread_mutex_t mutex;

#endif