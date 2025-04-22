#include "buffer.h"

/* the buffer and indexes */
buffer_item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void initialize_buffer() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
}

/* The functions */
int insert_item(buffer_item item) {
    // If the buffer is full, if current in is the same as out
    if (((in + 1) % BUFFER_SIZE) == out) {
        return -1;
    }

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    return 0;
}

int remove_item(buffer_item *item) {
    // If the buffer is empty, if current in is at index out
    if (in == out) {
        return -1;
    }

    *item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    return 0;
}
