#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "buffer.h"
#include "producer.c"
#include "consumer.c"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <sleep_time> <num_producers> <num_consumers>\n", argv[0]);
        return -1;
    }

    int sleep_time = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);

    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];

    initialize_buffer();
    srand(time(NULL));

    for (int i = 0; i < num_producers; i++)
        pthread_create(&producers[i], NULL, producer, NULL);

    for (int i = 0; i < num_consumers; i++)
        pthread_create(&consumers[i], NULL, consumer, NULL);

    sleep(sleep_time);

    // Cleanup and exit
    printf("Terminating after %d seconds\n", sleep_time);
    exit(0);
}
