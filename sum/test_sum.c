#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sum.h"

int main(int argc, char* argv[]) {
    int size = 100000000; // default size, can increase or set from cmd
    int num_threads = 4;  // default threads

    if (argc > 1) size = atoi(argv[1]);
    if (argc > 2) num_threads = atoi(argv[2]);

    int *data = malloc(sizeof(int) * size);
    if (!data) {
        printf("Failed to allocate memory\n");
        return 1;
    }

    // Initialize the array with all 1s, so sum = size
    for (int i = 0; i < size; i++) {
        data[i] = 1;
    }

    clock_t start, end;
    double time_taken;

    start = clock();
    long seq_sum = sequential_sum(data, size);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // ms
    printf("Sequential sum: %ld, Time: %.3f ms\n", seq_sum, time_taken);

    start = clock();
    long threaded_sum_result = threaded_sum(data, size, num_threads);
    end = clock();
    time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("Threaded sum (%d threads): %ld, Time: %.3f ms\n", num_threads, threaded_sum_result, time_taken);

    if (seq_sum == threaded_sum_result) {
        printf("Success: Both sums match!\n");
        printf("Speedup: %.2fx\n", (double)seq_sum / time_taken);
    } else {
        printf("Error: Sums do not match!\n");
    }

    free(data);
    return 0;
}
