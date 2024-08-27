#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int count = 0;  // Number of items in the buffer

// Function for Producer
void producer(int id) {
    for (int i = 0; i < 20; i++) {
        int produced = 0;
        while (!produced) {
            #pragma omp critical
            {
                if (count < BUFFER_SIZE) {  // Only produce if buffer is not full
                    buffer[count] = i;
                    count++;
                    printf("Producer %d produced: %d\n", id, i);
                    produced = 1;
                }
            }
            #pragma omp flush(count) // Ensure the latest count value is visible
        }
    }
}

// Function for Consumer
void consumer(int id) {
    for (int i = 0; i < 20; i++) {
        int consumed = 0;
        while (!consumed) {
            #pragma omp critical
            {
                if (count > 0) {  // Only consume if buffer is not empty
                    int item = buffer[--count];
                    printf("Consumer %d consumed: %d\n", id, item);
                    consumed = 1;
                }
            }
            #pragma omp flush(count) // Ensure the latest count value is visible
        }
    }
}

int main() {
    omp_set_num_threads(4); // Setting the number of threads

    double start, end;

    start=omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            producer(1); // Producer 1
        }
        #pragma omp section
        {
            consumer(1); // Consumer 1
        }
        #pragma omp section
        {
            producer(2); // Producer 2
        }
        #pragma omp section
        {
            consumer(2); // Consumer 2
        }
    }
    end=omp_get_wtime();

    printf("Time analysis = %lf  ",end-start);

    return 0;
}
