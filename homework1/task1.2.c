#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isRepeat(int array[], int size, int i)
{
    for (int j = 0; j < i; j++)
        if (array[j] == array[i])
            return true;
    return false;
}

int getMaximumRepeatedElement(int array[], int size)
{
    int max = array[0];
    int maxIndex = 0;
    bool isFound = false;
    for (int i = 1; i < size; i++) {
        if ((array[i] >= max) && (isRepeat(array, size, i))) {
            max = array[i];
            maxIndex = i;
            isFound = true;
        }
    }
    if (isFound)
        return maxIndex;
    else
        return -1;
}

int main()
{
    printf("Input size of array\n");
    int size = 0;
    scanf("%d", &size);
    int* array = calloc(size, sizeof(int));
    printf("Input %d integers\n", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &array[i]);
    int maxIndex = 0;
    maxIndex = getMaximumRepeatedElement(array, size);
    if (maxIndex >= 0)
        printf("maximum value, repeated more than 1 time: %d", array[maxIndex]);
    else
        printf("there are no repeated elements in the array");
    free(array);
    return 0;
}