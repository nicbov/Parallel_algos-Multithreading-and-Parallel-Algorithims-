#include "sum.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int* arr;
    int start;
    int end;
    long partial_sum;
} ThreadData;

long sequential_sum(int* arr, int size) {
    long sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

void* thread_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    data->partial_sum = 0;
    for (int i = data->start; i < data->end; i++) {
        data->partial_sum += data->arr[i];
    }
    return NULL;
}

long threaded_sum(int* arr, int size, int num_threads) {
    pthread_t* threads = malloc(sizeof(pthread_t) * num_threads);
    ThreadData* thread_data = malloc(sizeof(ThreadData) * num_threads);
    int chunk_size = size / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].arr = arr;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == num_threads - 1) ? size : (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, thread_sum, &thread_data[i]);
    }

    long total_sum = 0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += thread_data[i].partial_sum;
    }

    free(threads);
    free(thread_data);
    return total_sum;
}
