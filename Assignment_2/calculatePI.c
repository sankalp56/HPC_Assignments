#include <stdio.h>
#include <omp.h>

int main() {
    long long int n = 1000000; // Number of rectangles
    double pi, sum = 0.0;
    double step = 1.0 / n;
    double start, end;
     start = omp_get_wtime();

    // Parallelize the loop using OpenMP
    #pragma omp parallel
    {
        double x;
        double local_sum = 0.0;

        #pragma omp for
        for (long long int i = 0; i < n; i++) {
            x = (i + 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }

        #pragma omp atomic
        sum += local_sum;
    }
     end = omp_get_wtime();

    pi = sum * step;
    printf("Approximation of Pi = %lf\n", pi);
    printf("Time: %lf seconds\n", end - start);


    return 0;
}








// int main() {
//     long long int n = 1000000; // Number of rectangles
//     double pi, sum = 0.0;
//     double step = 1.0 / n;
//     double start, end;

//     // Start timing
//     start = omp_get_wtime();

//     // Sequential loop for Pi calculation
//     for (long long int i = 0; i < n; i++) {
//         double x = (i + 0.5) * step;
//         sum += 4.0 / (1.0 + x * x);
//     }

//     // End timing
//     end = omp_get_wtime();

//     pi = sum * step;
//     printf("Approximation of Pi = %lf\n", pi);
//     printf("Time: %lf seconds\n", end - start);

//     return 0;
// }