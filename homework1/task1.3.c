#include <stdio.h>

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}


int main()
{
    int n = 0, m = 0;
    printf("Input intgers m, n \n");
    scanf("%d%d", &m, &n);
    int* array = calloc(n + m, sizeof(int));
    printf("Input %d integers\n", n + m);
    for (int i = 0; i < n + m; i++)
        scanf("%d", &array[i]);
    for (int i = m - 1; i >= 0; i--)
        for (int j = i; j < i + n; j++)
            swap(&array[j], &array[j + 1]);
    printf("Start of array of length %d and end of length %d were swapped: \n", m, n);
    for (int i = 0; i < n + m; i++)
        printf("%d ", array[i]);
    free(array);
}

