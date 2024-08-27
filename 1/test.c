#include <stdio.h>
#include <omp.h>

int main()
{


    // Record the start time
    double start_time = omp_get_wtime();

#pragma omp parallel
    {
        // Each thread prints "Hello, world!!"
        printf("Hello, world!! from thread %d\n", omp_get_thread_num());
    }

    // Record the end time
    double end_time = omp_get_wtime();
    
    // Print the time taken by the parallel region
    printf("Time taken by the parallel region: %f seconds\n", end_time - start_time);

    return 0;
}
