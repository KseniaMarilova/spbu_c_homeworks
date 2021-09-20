#include <stdio.h>

void outputPrimeNumbers(int highestNumber)
{
    int *is—omposite = calloc(highestNumber+1, sizeof(int));
    int div = 2;
    while (div <= highestNumber) {
        for (int i = 2 * div; i <= highestNumber; i += div)
            is—omposite[i] = 1;
        div++;
        while (is—omposite[div]) div++;
    }
    printf("Prime numbers not exceeding %d: \n", highestNumber);
    for (int i = 2; i <= highestNumber; i++)
        if (!is—omposite[i])
            printf("%d ", i);
    free(is—omposite);
}

int main() {
    printf("Input integer number\n");
    int highestNumber = 0;
    scanf("%d", &highestNumber);
    outputPrimeNumbers(highestNumber);
}