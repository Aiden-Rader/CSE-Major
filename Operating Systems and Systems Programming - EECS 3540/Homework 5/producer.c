// How the producer works:

// while (1) {
//     sleep(rand time);
//     buffer_item item = rand();
//     wait(empty);     // wait for empty slot
//     wait(mutex);     // lock buffer
//     insert_item(item);
//     signal(mutex);   // unlock buffer
//     signal(full);    // signal item added
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "buffer.h"

void *producer(void *param) {
    buffer_item item;

    while (1) {
        sleep(rand() % 3);
        item = rand();

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        if (insert_item(item) == 0)
            printf("Producer produced: %d\n", item);
        else
            fprintf(stderr, "Error inserting item\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

