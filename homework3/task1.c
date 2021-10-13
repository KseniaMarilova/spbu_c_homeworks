#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 16

bool* add(bool* firstBinary, bool* secondBinary)
{
    bool* result = calloc(SIZE, sizeof(bool));
    int carry = 0;
    for (int i = 0; i < SIZE; i++) {
        result[i] = (firstBinary[i] + secondBinary[i] + carry) % 2;
        carry = (firstBinary[i] + secondBinary[i] + carry) / 2;
    }
    return result;
}

bool* inverse(bool* binary)
{
    for (int i = 0; i < SIZE; i++)
        binary[i] = !binary[i];
    return binary;
}

bool* minus(bool* binary)
{
    binary = inverse(binary);
    bool* one = calloc(SIZE, sizeof(bool));
    one[0] = 1;
    bool* result = add(binary, one);
    free(one);
    return result;
}

bool* decimalToBinary(int decimal)
{
    bool* binary = calloc(SIZE, sizeof(bool));
    int sign = 1;
    if (decimal < 0)
        sign = -1;
    decimal = abs(decimal);
    int i = 0;
    while (decimal > 0) {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
        i++;
    }
    if (sign < 0) {
        binary = minus(binary);
    }
    return binary;
}

int pow(int x, int y)
{
    int result = 1;
    for (int i = 0; i < y; i++) {
        result *= x;
    }
    return result;
}
int binaryToDecimal(bool* binary)
{
    int decimal = 0;
    int sign = 1;
    if (binary[SIZE - 1]) {
        sign = -1;
        bool* minusOne = decimalToBinary(-1);
        binary = add(binary, minusOne);
        free(minusOne);
        binary = inverse(binary);
    }
    for (int i = 0; i < SIZE - 2; i++)
        decimal += pow(2, i) * binary[i];
    decimal = decimal * sign;
    return decimal;
}

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
    bool* sum = add(firstBinary, secondBinary);
    printf("\nsum of numbers in binary code (two's complement): ");
    printBinary(sum);
    printf("\nsum of numbers in decimal code: ");
    printf("%d", binaryToDecimal(sum));
    free(firstBinary);
    free(secondBinary);
    free(sum);
    return 0;
}