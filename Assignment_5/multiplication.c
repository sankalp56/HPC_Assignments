#include <stdio.h>
#include <omp.h>

int main() {
    int Aryabhatta = 10;
    double start, end;

    start=omp_get_wtime();

    #pragma omp parallel private(Aryabhatta)
    {
        int thread_id = omp_get_thread_num();
        int result = thread_id * Aryabhatta;
        printf("Thread %d: %d * %d = %d\n", thread_id, thread_id, Aryabhatta, result);
    }
    end=omp_get_wtime();

    printf("Time Analysis = %lf  ", end-start);

    return 0;
}
