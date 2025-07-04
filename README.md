Parallel Algorithms: Multithreaded Sum and Parallel Sort


This project demonstrates the implementation and benchmarking of parallel algorithms using C and pthreads, specifically:

Sum of array elements: comparing sequential vs multi-threaded sum of a large integer array.
Sorting a 2D matrix: comparing sequential vs parallel sorting of rows in a matrix.

It shows how parallelism can significantly speed up compute-heavy tasks by leveraging multiple CPU cores.

Why This Project?
Parallel programming is essential for modern software performance optimization. This project explores:

How to divide workloads for threads.
Synchronization and safe data sharing.
Measuring performance speedups and scalability.
Using tools like CMake and Makefiles for cross-platform builds.

I learned how to structure C projects for multithreading, properly manage memory, and benchmark for meaningful speedup analysis.

Prerequisites
Make sure you have these installed on your system:

C compiler (gcc, clang, or AppleClang)

CMake (version 3.10+ recommended)

Make (usually pre-installed on macOS/Linux)

pthread library (usually included with standard C libraries)

To install CMake on macOS using Homebrew:

brew install cmake
On Ubuntu/Debian:

sudo apt-get update
sudo apt-get install cmake build-essential
Setup & Build
Clone the repo:

git clone https://github.com/nicbov/parallel_algos.git
cd parallel_algos
Build using the Makefile (this runs CMake and builds both sum and parsort tests):

make
Run Tests and Performance Benchmark
Run the full suite with default parameters:

make && ./build/test_sum && echo && ./build/parsort/test_parsort
Custom Input Arguments
You can pass optional command-line arguments to specify:

For test_sum: array size (default: 100,000,000)

Example:

./build/test_sum 50000000
For test_parsort: matrix rows, matrix columns, number of threads (defaults: 1000, 1000, 4)

Example:

./build/parsort/test_parsort 2000 2000 8
Expected Output Format
The programs print timing and speedup results in a markdown-friendly table format:

## Performance Results

### Array Sum (100000000 integers)

| Threads | Time (ms) | Speedup |
|---------|-----------|---------|
| 1       | 130.000   | 1.00x   |
| 2       | 70.000    | 1.85x   |
| 4       | 40.000    | 3.25x   |

### Matrix Sort (1000 x 1000 integers)

| Threads | Time (ms) | Speedup |
|---------|-----------|---------|
| 1       | 60.000    | 1.00x   |
| 2       | 30.000    | 2.00x   |
| 4       | 15.000    | 4.00x   |

What I Learned:

Writing clean C code for multithreaded computation.
Using pthreads to manage threads safely and efficiently.
Benchmarking and profiling for performance measurement.
Using CMake and Makefiles for cross-platform builds and easy compilation.
Handling large data sets and ensuring correctness with parallel algorithm.

License
This project is open source under the MIT License.

