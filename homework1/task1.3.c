#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void swapSegments(int array[], int startLength, int endLength)
{
    for (int i = startLength - 1; i >= 0; i--)
        for (int j = i; j < i + endLength; j++)
            swap(&array[j], &array[j + 1]);
}
int main()
{
    int startLength = 0;
    int endLength = 0;
    printf("Input 2 integer numbers: length of starting segment, length of ending segment \n");
    scanf("%d%d", &startLength, &endLength);
    int arraySize = startLength + endLength;
    int* array = calloc(arraySize, sizeof(int));
    printf("Input %d integers\n", arraySize);
    for (int i = 0; i < arraySize; i++)
        scanf("%d", &array[i]);
    swapSegments(array, startLength, endLength);
    printf("Start of array of length %d and end of length %d were swapped: \n", startLength, endLength);
    for (int i = 0; i < arraySize; i++)
        printf("%d ", array[i]);
    free(array);
    return 0;
}