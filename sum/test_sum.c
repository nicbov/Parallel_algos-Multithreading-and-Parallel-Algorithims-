#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sum.h"

double time_in_ms(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
}

int main(int argc, char* argv[]) {
    int size = 100000000; // Default array size
    int thread_counts[] = {1, 2, 4, 8};
    int num_configs = sizeof(thread_counts) / sizeof(thread_counts[0]);

    if (argc > 1) {
        int parsed = atoi(argv[1]);
        if (parsed > 0) size = parsed;
    }

    int* data = malloc(sizeof(int) * size);
    if (!data) {
        fprintf(stderr, "❌ Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < size; i++) {
        data[i] = 1; // Makes the correct sum equal to the array size
    }

    // Run and time sequential sum
    clock_t start = clock();
    long seq_sum = sequential_sum(data, size);
    clock_t end = clock();
    double seq_time = time_in_ms(start, end);

    // Output results in Markdown format
    printf("## 📊 Performance Results\n\n");
    printf("### ➕ Array Summation (%d integers)\n\n", size);
    printf("| Threads | Time (ms) | Speedup |\n");
    printf("|---------|-----------|---------|\n");

    for (int i = 0; i < num_configs; i++) {
        int threads = thread_counts[i];

        start = clock();
        long par_sum = threaded_sum(data, size, threads);
        end = clock();
        double par_time = time_in_ms(start, end);

        if (par_sum != seq_sum) {
            printf("| %-7d |   ERROR   | MISMATCH |\n", threads);
            continue;
        }

        double speedup = seq_time / par_time;
        printf("| %-7d | %-9.3f | %.2fx   |\n", threads, par_time, speedup);
    }

    free(data);
    return 0;
}
