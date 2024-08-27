#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void solve(int size, int num_threads) {
    int i, j;
    double start_time, end_time;

    int **matrixA = (int **)malloc(size * sizeof(int *));
    int **matrixB = (int **)malloc(size * sizeof(int *));
    int **matrixC = (int **)malloc(size * sizeof(int *));
    
    for (i = 0; i < size; i++) {
        matrixA[i] = (int *)malloc(size * sizeof(int));
        matrixB[i] = (int *)malloc(size * sizeof(int));
        matrixC[i] = (int *)malloc(size * sizeof(int));
    }
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            matrixA[i][j] = i + j;
            matrixB[i][j] = i - j;
        }
    }
    omp_set_num_threads(num_threads);
    start_time = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    end_time = omp_get_wtime();
    printf("Size: %d, Threads: %d, Time: %f seconds\n", size, num_threads, end_time - start_time);
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int num_threads[] = {1, 2, 4, 8, 16};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            solve(sizes[i], num_threads[j]);

        }
                    printf("\n");
    }

    return 0;
}