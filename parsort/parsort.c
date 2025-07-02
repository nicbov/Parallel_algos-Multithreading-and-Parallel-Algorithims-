#include "parsort.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    int** matrix;
    int start_row;
    int end_row;
    int cols;
} ThreadData;

static int compare_ints(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

void sequential_parsort(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        qsort(matrix[i], cols, sizeof(int), compare_ints);
    }
}

// Thread function for parallel sorting
void* thread_sort_rows(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->start_row; i < data->end_row; i++) {
        qsort(data->matrix[i], data->cols, sizeof(int), compare_ints);
    }
    return NULL;
}

void parallel_parsort(int** matrix, int rows, int cols, int num_threads) {
    pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
    ThreadData* thread_data = malloc(num_threads * sizeof(ThreadData));

    int chunk_size = rows / num_threads;
    int remainder = rows % num_threads;

    int current_row = 0;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].matrix = matrix;
        thread_data[i].start_row = current_row;
        thread_data[i].end_row = current_row + chunk_size + (i < remainder ? 1 : 0);
        thread_data[i].cols = cols;

        pthread_create(&threads[i], NULL, thread_sort_rows, &thread_data[i]);
        current_row = thread_data[i].end_row;
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(thread_data);
}
