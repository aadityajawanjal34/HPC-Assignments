#include <stdio.h>
#include <omp.h>
int main(){
    int size, scalar, num_threads;
    printf("Enter the size of the vector: ");
    scanf("%d", &size);
    printf("Enter the scalar value to add: ");
    scanf("%d", &scalar);
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    int vector[size];
    for (int i = 0; i < size; i++)
        vector[i] = i + 1;
    omp_set_num_threads(num_threads);

    #pragma omp parallel for
    for (int i = 0; i < size; i++)
    {
        printf("Thread %d: Adding %d at index %d\n", omp_get_thread_num(), scalar, i);
        vector[i] += scalar;
    }

    printf("Resultant vector:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", vector[i]);
    }
    printf("\n");

    return 0;
}
