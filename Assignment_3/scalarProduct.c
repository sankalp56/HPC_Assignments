#include <stdio.h>
#include <omp.h>

int main() {
    int n = 1000; // Size of the vectors
    int A[n], B[n];
    long long int dot_product = 0;
    double start,end;

    // Initialize vectors A and B
    for (int i = 0; i < n; i++) {
        A[i] = i + 1; // Example initialization
        B[i] = i + 2; // Example initialization
    }

    start=omp_get_wtime();
    // Compute the dot product in parallel
    #pragma omp parallel for reduction(+:dot_product) schedule(static)
    for (int i = 0; i < n; i++) {
        dot_product += (long long int)A[i] * B[i];
    }
    end=omp_get_wtime();
    printf("Dot Product = %lld\n", dot_product);
    printf("Time analysis = %lf\n", end-start);

    return 0;
}
