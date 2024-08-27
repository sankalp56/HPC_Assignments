#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 1) return n;

    int x, y;
    #pragma omp task shared(x)
    x = fibonacci(n - 1);

    #pragma omp task shared(y)
    y = fibonacci(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 10;
    int fib;

    double start, end;

    start=omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        fib = fibonacci(n);
    }
    end=omp_get_wtime();
    printf("Fibonacci(%d) = %d\n", n, fib);
    printf("Time Analysis = %lf   ", end-start);
    return 0;
}
