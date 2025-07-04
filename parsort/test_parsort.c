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
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = rand() % 1000;
}

// Helper: check if two matrices are equal
int matrices_equal(int** m1, int** m2, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (m1[i][j] != m2[i][j]) return 0;
    return 1;
}

// Timer utility
double timediff_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0 +
           (end.tv_nsec - start.tv_nsec) / 1e6;
}

// Main
int main(int argc, char* argv[]) {
    int rows = 1000;
    int cols = 1000;
    int thread_configs[] = {1, 2, 4, 8};
    int num_configs = sizeof(thread_configs) / sizeof(thread_configs[0]);

    if (argc >= 3) {
        rows = atoi(argv[1]);
        cols = atoi(argv[2]);
    }

    srand((unsigned)time(NULL));

    // Generate original matrix
    int** original = allocate_matrix(rows, cols);
    fill_matrix_random(original, rows, cols);

    // Create sequential copy
    int** seq_matrix = allocate_matrix(rows, cols);
    for (int i = 0; i < rows; i++)
        memcpy(seq_matrix[i], original[i], cols * sizeof(int));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    sequential_parsort(seq_matrix, rows, cols);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double seq_time = timediff_ms(start, end);

    printf("## 📊 Performance Results\n\n");
    printf("### 🧮 Matrix Sort (%d x %d integers)\n\n", rows, cols);
    printf("| Threads | Time (ms) | Speedup |\n");
    printf("|---------|-----------|---------|\n");

    for (int i = 0; i < num_configs; i++) {
        int threads = thread_configs[i];

        // Copy original into parallel matrix
        int** par_matrix = allocate_matrix(rows, cols);
        for (int j = 0; j < rows; j++)
            memcpy(par_matrix[j], original[j], cols * sizeof(int));

        clock_gettime(CLOCK_MONOTONIC, &start);
        parallel_parsort(par_matrix, rows, cols, threads);
        clock_gettime(CLOCK_MONOTONIC, &end);
        double par_time = timediff_ms(start, end);

        if (!matrices_equal(seq_matrix, par_matrix, rows, cols)) {
            printf("Error: Output mismatch with %d threads\n", threads);
        } else {
            double speedup = seq_time / par_time;
            printf("| %-7d | %-9.3f | %.2fx   |\n", threads, par_time, speedup);
        }

        free_matrix(par_matrix, rows);
    }

    // Cleanup
    free_matrix(original, rows);
    free_matrix(seq_matrix, rows);

    return 0;
}
