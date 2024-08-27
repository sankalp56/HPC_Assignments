#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    int array[ARRAY_SIZE];
    int total_sum = 0;
    double start, end;

    start=omp_get_wtime();

    // Initialize array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1; // Sample data
    }

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++) {
            #pragma omp critical
            {
                total_sum += array[i]; // Critical section to avoid data race
            }
        }
    }

    end=omp_get_wtime();
zzzzzz
    printf("Total sum: %d\n", total_sum);

    printf("Time Analysis = %lf   ", end-start);
     return 0;
}
