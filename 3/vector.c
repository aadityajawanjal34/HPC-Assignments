#include <stdio.h>
#include <omp.h>

void vector_scalar_add_static(int vector[], int size, int scalar, int chunk_size, int num_threads) {
    omp_set_num_threads(num_threads);
    double start_time = omp_get_wtime();

    #pragma omp parallel for schedule(static, chunk_size)
    for (int i = 0; i < size; i++) {
        vector[i] += scalar;
    }

    double end_time = omp_get_wtime();
    printf("STATIC - Chunk Size: %d, Threads: %d, Time: %f seconds\n", chunk_size, num_threads, end_time - start_time);
}


void vector_scalar_add_dynamic(int vector[], int size, int scalar, int chunk_size, int num_threads) {
    omp_set_num_threads(num_threads);
    double start_time = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, chunk_size)
    for (int i = 0; i < size; i++) {
        vector[i] += scalar;
    }

    double end_time = omp_get_wtime();
    printf("DYNAMIC - Chunk Size: %d, Threads: %d, Time: %f seconds\n", chunk_size, num_threads, end_time - start_time);
}

void vector_scalar_add_nowait(int vector[], int size, int scalar, int num_threads) {
    omp_set_num_threads(num_threads);
    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp for schedule(static, 4) nowait
        for (int i = 0; i < size; i++) {
            vector[i] += scalar;
        }
        // Additional computation can be placed here without waiting for all threads to finish the loop
    }

    double end_time = omp_get_wtime();
    printf("NOWAIT - Threads: %d, Time: %f seconds\n", num_threads, end_time - start_time);
}

int main() {
    int size = 200;
    int vector[size];
    int scalar = 5;
    
    for (int i = 0; i < size; i++) {
        vector[i] = i;
    }

    int num_threads[] = {2, 4, 8};
    int chunk_sizes[] = {1, 2, 4, 8};

    // Testing STATIC schedule
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            // Reset vector
            for (int k = 0; k < size; k++) {
                vector[k] = k;
            }
            vector_scalar_add_static(vector, size, scalar, chunk_sizes[j], num_threads[i]);
        }
    }
    printf("\n");

    // Testing DYNAMIC schedule
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            // Reset vector
            for (int k = 0; k < size; k++) {
                vector[k] = k;
            }
            vector_scalar_add_dynamic(vector, size, scalar, chunk_sizes[j], num_threads[i]);
        }
    }

    // Demonstrate the NOWAIT clause
    vector_scalar_add_nowait(vector, size, scalar, 4);

    return 0;
}
