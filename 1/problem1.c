#include <stdio.h>
#include <omp.h>

int main()
{
    int numThreads;

    printf("Enter the number of threads: ");
    scanf("%d", &numThreads);

    printf("Sequential Execution: \n");

    double start = omp_get_wtime();

    // Sequential Execution
    for (int i = 0; i < numThreads; i++)
    {
        // Perform some computational task
        double sum = 0.0;
        for (int j = 0; j < 1000000; j++)
        {
            sum += j * 0.001; // Simple computation to keep CPU busy
        }

        printf("Sequential! --> Hello, World! Thread %d Sum: %f\n", i, sum);
    }

    double end = omp_get_wtime();
    double seq = end - start;

    printf("\nParallel Execution: \n");
    omp_set_num_threads(numThreads);

    start = omp_get_wtime();

    // Parallel Execution
#pragma omp parallel
    {
        // Perform some computational task
        double sum = 0.0;S
        for (int j = 0; j < 1000000; j++)
        {
            sum += j * 0.001; // Simple computation to keep CPU busy
        }

        printf("Parallel! --> Hello, World! Thread %d Sum: %f\n", omp_get_thread_num(), sum);
    }

    end = omp_get_wtime();
    double para = end - start;

    printf("\nExecution time for Sequential Processing: %f seconds\n", seq);
    printf("Execution time for Parallel Processing: %f seconds\n", para);

    return 0;
}
