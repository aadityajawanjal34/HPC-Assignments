#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main()
{
    int num_threads = 64;
    int num_iterations = 1e9;
    while (num_threads > 0)
    {
        double pi = 0.0;
        omp_set_num_threads(num_threads);
        double start_time = omp_get_wtime();
        int count = 0;
        #pragma omp parallel
        {
            unsigned int seed = (unsigned int)time(NULL) ^ omp_get_thread_num();
            int local_count = 0;

            #pragma omp for
            for (int i = 0; i < num_iterations; i++)
            {
                double x = (double)rand_r(&seed) / RAND_MAX;
                double y = (double)rand_r(&seed) / RAND_MAX;
                if (x * x + y * y <= 1.0)
                    local_count++;
            }
            #pragma omp atomic
            count += local_count;
        }
        pi = 4.0 * (double)count / (double)num_iterations;
        double end_time = omp_get_wtime();
        printf("Calculated Pi: %f\n", pi);
        printf("%f seconds for %d threads\n", end_time - start_time, num_threads);

        num_threads /= 2;
    }

    double start_time = omp_get_wtime();
    int count = 0;
    unsigned int seed = (unsigned int)time(NULL);
    for (int i = 0; i < num_iterations; i++)
    {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        if (x * x + y * y <= 1.0)
            count++;
    }
    double pi = 4.0 * (double)count / (double)num_iterations;
    double end_time = omp_get_wtime();

    printf("Calculated Pi: %f\n", pi);
    printf("Time taken for sequential execution: %f seconds\n", end_time - start_time);

    return 0;
}