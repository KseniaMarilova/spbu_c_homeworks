#include <stdio.h>
#include <stdlib.h>

int* merge(int* array1, int size1, int* array2, int size2)
{
    int* result = calloc(size1 + size2, sizeof(int));
    int current1 = 0;
    int current2 = 0;
    for (int i = 0; current1 < size1 && current2 < size2; i++) {
        if (array1[current1] > array2[current2]) {
            result[i] = array1[current1];
            current1++;
        } else {
            result[i] = array2[current2];
            current2++;
        }
    }
    if (current1 < size1)
        for (int i = current1 + current2; i < size1 + size2; i++)
            result[i] = array1[i - current2];
    if (current2 < size2)
        for (int i = current1 + current2; i < size1 + size2; i++)
            result[i] = array2[i - current1];
    return result;
}

int main()
{
    int size1 = 0;
    int size2 = 0;
    printf("input the number of notes in 1st stack");
    scanf("%d", &size1);
    int* array1 = calloc(size1, sizeof(int));
    printf("enter the complexity of the notes in 1st stack descending order");
    for (int i = 0; i < size1; i++)
        scanf("%d", &array1[i]);
    printf("input the number of notes in 2nd stack");
    scanf("%d", &size2);
    int* array2 = calloc(size2, sizeof(int));
    printf("enter the complexity of the notes in 2nd stack descending order");
    for (int i = 0; i < size2; i++)
        scanf("%d", &array2[i]);
    int* mergedArray = merge(array1, size1, array2, size2);
    printf("united stack:\n");
    for (int i = 0; i < size1 + size2; i++)
        printf("%d ", mergedArray[i]);
    free(array1);
    free(array2);
    free(mergedArray);
    return 0;
}