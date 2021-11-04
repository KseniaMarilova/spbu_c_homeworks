#include "../library/MergeSort/MergeSort.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("input size of array:\n");
    int size = 0;
    scanf("%d", &size);
    int* array = calloc(size, sizeof(int));
    printf("input %d numbers:\n", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &array[i]);
    sort(array, size);
    printf("array sorted in ascending order:\n");
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    free(array);
    return 0;
}