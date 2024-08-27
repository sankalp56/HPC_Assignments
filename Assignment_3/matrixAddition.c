#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void matrix_addition(int size, int num_threads) {
    int **A, **B, **C;
    double start, end;

    // Allocate memory for matrices
    A = (int **)malloc(size * sizeof(int *));
    B = (int **)malloc(size * sizeof(int *));
    C = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        A[i] = (int *)malloc(size * sizeof(int));
        B[i] = (int *)malloc(size * sizeof(int));
        C[i] = (int *)malloc(size * sizeof(int));
    }

    // Initialize matrices A and B with some values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = i + j;
            B[i][j] = i - j;
        }
    }

    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Start timing
    start = omp_get_wtime();

    // Perform matrix addition in parallel
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // End timing
    end = omp_get_wtime();

    // Print runtime
    printf("Matrix Size: %d, Number of Threads: %d, Time: %lf seconds\n", size, num_threads, end - start);

    // Free allocated memory
    for (int i = 0; i < size; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_threads_list[] = {2, 4, 8};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int num_threads = sizeof(num_threads_list) / sizeof(num_threads_list[0]);

    double start,end;

    start=omp_get_wtime();

    for (int i = 0; i < num_sizes; i++) {
        for (int j = 0; j < num_threads; j++) {
            matrix_addition(sizes[i], num_threads_list[j]);
        }
    }
    end=omp_get_wtime();

    printf("Time analysis =%lf", end-start);

    return 0;
}
