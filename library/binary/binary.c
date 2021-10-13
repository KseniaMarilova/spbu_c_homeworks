#include "binary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool* add(bool* firstBinary, bool* secondBinary)
{
    bool* result = calloc(SIZE, sizeof(bool));
    int carry = 0;
    for (int i = 0; i < SIZE; i++) {
        result[i] = (firstBinary[i] + secondBinary[i] + carry) & 0b1;
        carry = (firstBinary[i] + secondBinary[i] + carry) >> 1;
    }
    return result;
}

bool* bitShiftLeft(bool* binary, int positions)
{
    bool* result = calloc(SIZE, sizeof(bool));
    for (int i = 0; i < SIZE - positions; i++)
        result[i + positions] = binary[i];
    return result;
}

bool* multiply(bool* a, bool* b)
{
    bool* result = calloc(SIZE, sizeof(bool));
    bool* temporary = calloc(SIZE, sizeof(bool));
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++)
            temporary[i] = a[i] & b[j];
        temporary = bitShiftLeft(temporary, j);
        result = add(result, temporary);
    }
    free(temporary);
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
        binary[i] = decimal & 0b1;
        decimal = decimal >> 1;
        i++;
    }
    if (sign < 0) {
        binary = minus(binary);
    }
    return binary;
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
        decimal += binary[i] << i;
    decimal = decimal * sign;
    return decimal;
}