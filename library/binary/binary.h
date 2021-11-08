
#ifndef TASK3_BINARY_H
#define TASK3_BINARY_H

#include <stdbool.h>

#define SIZE 16

void printBinary(bool* binary);
bool* add(bool* firstBinary, bool* secondBinary);
bool* multiply(bool* a, bool* b);
bool* decimalToBinary(int decimal);
int binaryToDecimal(bool* binary);


#endif //TASK3_BINARY_H
