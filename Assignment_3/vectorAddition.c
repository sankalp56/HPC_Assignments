#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void vector_scalar_addition(int vector_size, int scalar, int schedule_type, int chunk_size) {
    int *vector = (int *)malloc(vector_size * sizeof(int));
    double start, end;

    // Initialize vector
    for (int i = 0; i < vector_size; i++) {
        vector[i] = i;
    }

    // Set the number of threads
    int num_threads = 4; // Adjust this as needed
    omp_set_num_threads(num_threads);

    // Start timing
    start = omp_get_wtime();

    // Perform vector-scalar addition
    #pragma omp parallel
    {
        if (schedule_type == 0) { // STATIC scheduling
            #pragma omp for schedule(static, chunk_size) nowait
            for (int i = 0; i < vector_size; i++) {
                vector[i] += scalar;
            }
        } else { // DYNAMIC scheduling
            #pragma omp for schedule(dynamic, chunk_size) nowait
            for (int i = 0; i < vector_size; i++) {
                vector[i] += scalar;
            }
        }
    }

    // End timing
    end = omp_get_wtime();

    // Print results
    printf("Vector Size: %d, Scalar: %d, Schedule Type: %s, Chunk Size: %d, Time: %lf seconds\n",
           vector_size, scalar, schedule_type == 0 ? "STATIC" : "DYNAMIC", chunk_size, end - start);

    printf("Time Analysis = %lf", end-start);

    // Free allocated memory
    free(vector);
}

int main() {
    int vector_size = 200; // Size of the vector
    int scalar = 10; // Scalar value to add

    // Test STATIC scheduling with different chunk sizes
    printf("STATIC Scheduling:\n");
    for (int chunk_size = 1; chunk_size <= 10; chunk_size++) {
        vector_scalar_addition(vector_size, scalar, 0, chunk_size);
    }

    // Test DYNAMIC scheduling with different chunk sizes
    printf("DYNAMIC Scheduling:\n");
    for (int chunk_size = 1; chunk_size <= 10; chunk_size++) {
        vector_scalar_addition(vector_size, scalar, 1, chunk_size);
    }

    return 0;
}
