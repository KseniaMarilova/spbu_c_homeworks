#include "MergeSort.h"
#include <stdlib.h>

void merge(int* a, int left, int right, int* buffer)
{
    int middle = (left + right) / 2;
    int currentLeft = left;
    int currentRight = middle + 1;
    for (int i = left; currentLeft <= middle && currentRight <= right; i++) {
        if (a[currentLeft] < a[currentRight]) {
            buffer[i] = a[currentLeft];
            currentLeft++;
        } else {
            buffer[i] = a[currentRight];
            currentRight++;
        }
    }
    if (currentRight <= right)
        for (int i = currentRight; i <= right; i++)
            buffer[i] = a[i];
    if (currentLeft <= middle + 1)
        for (int i = currentLeft; i <= middle; i++)
            buffer[i + (right - left + 1) / 2] = a[i];
    for (int i = left; i <= right; i++)
        a[i] = buffer[i];
}

void sortInterval(int* a, int left, int right, int* buffer)
{
    if (left < right) {
        int mid = (left + right) / 2;
        sortInterval(a, left, mid, buffer);
        sortInterval(a, mid + 1, right, buffer);
        merge(a, left, right, buffer);
    }
}

void sort(int* a, int size)
{
    int* buffer = calloc(size, sizeof(int));
    sortInterval(a, 0, size - 1, buffer);
    free(buffer);
}