#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "parsort.h"

// Helper: allocate a 2D matrix
int** allocate_matrix(int rows, int cols) {
    int** matrix = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }
    return matrix;
}

// Helper: free a 2D matrix
void free_matrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Helper: fill matrix with random values
void fill_matrix_random(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 1000;
        }
    }
}

// Helper: copy matrix
int** copy_matrix(int** matrix, int rows, int cols) {
    int** copy = allocate_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        memcpy(copy[i], matrix[i], cols * sizeof(int));
    }
    return copy;
}

// Helper: check if two matrices are equal
int matrices_equal(int** m1, int** m2, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (m1[i][j] != m2[i][j]) return 0;
        }
    }
    return 1;
}

double timediff_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 +
           (end.tv_nsec - start.tv_nsec) / 1e6;
}

int main(int argc, char* argv[]) {
    int rows = 1000;
    int cols = 1000;
    int num_threads = 4;

    if (argc >= 2) rows = atoi(argv[1]);
    if (argc >= 3) cols = atoi(argv[2]);
    if (argc >= 4) num_threads = atoi(argv[3]);

    srand((unsigned)time(NULL));

    int** matrix = allocate_matrix(rows, cols);
    fill_matrix_random(matrix, rows, cols);

    int** seq_copy = copy_matrix(matrix, rows, cols);
    int** par_copy = copy_matrix(matrix, rows, cols);

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    sequential_parsort(seq_copy, rows, cols);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double seq_time = timediff_ms(start, end);

    clock_gettime(CLOCK_MONOTONIC, &start);
    parallel_parsort(par_copy, rows, cols, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double par_time = timediff_ms(start, end);

    printf("Sequential sort time: %.3f ms\n", seq_time);
    printf("Parallel sort time (%d threads): %.3f ms\n", num_threads, par_time);

    if (matrices_equal(seq_copy, par_copy, rows, cols)) {
        printf("Success: Matrices match!\n");
        printf("Speedup: %.2fx\n", seq_time / par_time);
    } else {
        printf("Error: Matrices do not match!\n");
    }

    free_matrix(matrix, rows);
    free_matrix(seq_copy, rows);
    free_matrix(par_copy, rows);

    return 0;
}
