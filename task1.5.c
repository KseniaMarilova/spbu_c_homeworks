#include <stdio.h>

 void printLeft(int left[], int *size, int *stage)
 {
     for(int i = 0; i < (*size - *stage) / 2; i++) {
         printf("%5d", left[i]);
         left[i]--;
     }
}
void printRight(int right[], int *size, int *stage)
{
    for(int i = (*size - *stage) / 2 - 1; i >= 0; i--) {
        printf("%5d", right[i]);
        right[i]++;
    }
}

int main()
{
    int size = 0;
    printf("Input integer number n \n");
    scanf("%d", &size);
    printf("Numbers from 1 to n*n in a spiral: \n");
    int *left = calloc(size / 2 + 1, sizeof(int));
    int *right = calloc(size / 2 + 1, sizeof(int));
    int stage = size;
    while (stage >= 1) {
        printLeft(left, &size, &stage);
        left[(size - stage) / 2] = stage * (stage - 1);
        right[(size - stage) / 2] = (stage - 2) * (stage - 2) + 1;
        for(int i = 0; i < stage; i++)
            printf("%5d", stage * (stage - 1) + 1 + i);
        printRight(right, &size, &stage);
        printf("\n");
        stage -= 2;
    }
    stage = 3;
    while (stage <= size) {
        printLeft(left, &size, &stage);
        for(int i = stage - 1; i >= 0; i--)
            printf("%5d", stage * (stage - 3) + 3 + i);
        printRight(right, &size, &stage);
        stage += 2;
        printf("\n");
     }
    free(left);
    free(right);
 }