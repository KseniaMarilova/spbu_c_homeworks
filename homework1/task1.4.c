#include <stdio.h>

void outputPrimeNumbers(int highestNumber)
{
    int* isComposite = calloc(highestNumber + 1, sizeof(int));
    int div = 2;
    while (div <= highestNumber) {
        for (int i = 2 * div; i <= highestNumber; i += div)
            isComposite[i] = 1;
        div++;
        while (isComposite[div])
            div++;
    }
    printf("Prime numbers not exceeding %d: \n", highestNumber);
    for (int i = 2; i <= highestNumber; i++)
        if (!isComposite[i])
            printf("%d ", i);
    free(isComposite);
}

int main()
{
    printf("Input integer number\n");
    int highestNumber = 0;
    scanf("%d", &highestNumber);
    outputPrimeNumbers(highestNumber);
}