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
    bool* sum = multiply(firstBinary, secondBinary);
    printf("\nsum of numbers in binary code (two's complement): ");
    printBinary(sum);
    printf("\nsum of numbers in decimal code: ");
    printf("%d", binaryToDecimal(sum));
    free(firstBinary);
    free(secondBinary);
    free(sum);
    return 0;
}