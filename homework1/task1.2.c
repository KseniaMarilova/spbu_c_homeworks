#include <stdio.h>

int isRepeat(int array[], int size, int i)
{
    for (int j = 0; j < i; j++)
        if (array[j] == array[i])
            return 1;
    return 0;
}

int main()
{
    printf("Input size of array\n");
    int size = 0;
    scanf("%d", &size);
    int *array = calloc(size, sizeof(int));
    printf("Input %d integers\n", size);
    for (int i = 0; i < size; i++)
        scanf("%d", &array[i]);
    int max = array[0];
    int isFound = 0;
    for (int i = 1; i < size; i++) {
        if ((array[i] >= max) && (isRepeat(array, size, i))) {
            max = array[i];
            isFound = 1;
        }
    }
    if (isFound)
        printf("maximum value, repeated more than 1 time: %d", max);
    else
        printf("there are no repeated elements in the array");
    free(array);
}