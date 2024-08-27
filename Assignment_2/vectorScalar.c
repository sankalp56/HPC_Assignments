#include <stdio.h>
#include <omp.h>

int main() {
    int n = 1000; // Size of the vector
    int scalar = 5; // Scalar value to add
    int vector[n];
    
    double start, end;
     start = omp_get_wtime();
    // Initialize the vector with values 0 to n-1
    for (int i = 0; i < n; i++) {
        vector[i] = i;
    }

    // Parallelize the vector-scalar addition
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        vector[i] += scalar;
    }

    // Print the result (optional)
    printf("Resultant vector after scalar addition:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
    end = omp_get_wtime();

    printf("Time analysis= %lf", end-start);

    return 0;
}
