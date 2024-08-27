#include <stdio.h>
#include <omp.h>

int main() {
    double start, end;

    start=omp_get_wtime();
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("2\n");
        }
        #pragma omp section
        {
            printf("4\n");
        }
    }
    end=omp_get_wtime();

    printf("Time Analysis = %lf         ", end-start);
    return 0;
}
