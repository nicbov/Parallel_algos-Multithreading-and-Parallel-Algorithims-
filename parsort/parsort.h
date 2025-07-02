#ifndef PARSORT_H
#define PARSORT_H

void sequential_parsort(int** matrix, int rows, int cols);
void parallel_parsort(int** matrix, int rows, int cols, int num_threads);

#endif // PARSORT_H
