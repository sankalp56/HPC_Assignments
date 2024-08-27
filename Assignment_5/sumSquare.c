#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;
    double start, end;

    start=omp_get_wtime();

    #pragma omp parallel reduction(+:sum)
    {
        int thread_id = omp_get_thread_num();
        int square = thread_id * thread_id;
        printf("Thread %d: Square = %d\n", thread_id, square);
        sum += square;
    }

    end=omp_get_wtime();

    printf("Sum of squares of thread IDs: %d\n", sum);

    printf("Time analysis = %lf    ", end-start);
    return 0;
}
