#include <stdbool.h>
#include <stdio.h>

void findPrimeNumbers(bool isPrime[], int highestNumber)
{
    int div = 2;
    while (div <= highestNumber) {
        for (int i = 2 * div; i <= highestNumber; i += div)
            isPrime[i] = false;
        div++;
        while (!isPrime[div])
            div++;
    }
}

int main()
{
    printf("Input integer number\n");
    int highestNumber = 0;
    scanf("%d", &highestNumber);
    bool* isPrime = calloc(highestNumber + 1, sizeof(bool));
    for (int i = 2; i <= highestNumber; i++)
        isPrime[i] = true;
    findPrimeNumbers(isPrime, highestNumber);
    printf("Prime numbers not exceeding %d: \n", highestNumber);
    for (int i = 2; i <= highestNumber; i++)
        if (isPrime[i])
            printf("%d ", i);
    free(isPrime);
    return 0;
}