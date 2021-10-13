#include "../library/binary/binary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printBinary(bool* binary)
{
    for (int i = SIZE - 1; i >= 0; i--) {
        printf("%d", binary[i]);
    }
}

int main()
{
    int firstDecimal = 0, secondDecimal = 0;
    printf("Input first decimal number:\n");
    scanf("%d", &firstDecimal);
    bool* firstBinary = decimalToBinary(firstDecimal);
    printf("Input second decimal number:\n");
    scanf("%d", &secondDecimal);
    bool* secondBinary = decimalToBinary(secondDecimal);
    printf("first number in binary code (two's complement): ");
    printBinary(firstBinary);
    printf("\nsecond number in binary code (two's complement): ");
    printBinary(secondBinary);
    bool* product = multiply(firstBinary, secondBinary);
    printf("\nproduct of numbers in binary code (two's complement): ");
    printBinary(product);
    printf("\nproduct of numbers in decimal code: ");
    printf("%d", binaryToDecimal(product));
    free(firstBinary);
    free(secondBinary);
    free(product);
    return 0;
}