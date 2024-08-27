#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
void bubbleSort(int *arr, int n, int ascending) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            // Compare elements and swap based on the ascending flag
            if (ascending ? (arr[j] > arr[j+1]) : (arr[j] < arr[j+1])) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
int main() {
    int n = 5;
    int a[] = {1, 3, -5, 7, 9};
    int b[] = {2, -6, 4, -8, 10};
    int result = 0;
    bubbleSort(a, n, 1);
    bubbleSort(b, n, 0);
    #pragma omp parallel for reduction(+:result) schedule(static, 2) ordered
    for (int i = 0; i < n; i++) {
        int product = a[i] * b[i];
        #pragma omp ordered
        {
            result += product; 
        }
    }
    printf("Minimum Scalar Product: %d\n", result);
    return 0;
}