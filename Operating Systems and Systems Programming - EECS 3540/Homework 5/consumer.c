// How the consumer works:

// while (1) {
//     sleep(rand time);
//     wait(full);      // wait for item
//     wait(mutex);     // lock buffer
//     remove_item(&item);
//     signal(mutex);   // unlock buffer
//     signal(empty);   // signal slot freed
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "buffer.h"

void *consumer(void *param) {
    buffer_item item;

    while (1) {
        sleep(rand() % 3);

        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        if (remove_item(&item) == 0)
            printf("Consumer consumed: %d\n", item);
        else
            fprintf(stderr, "Error removing item\n");

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}
