#include <stdio.h>
#include <stdlib.h>

typedef union Number {
    double value;
    char binaryForm[8];
} Number;

int getBit(char number, int position)
{
    char bit = (number >> position) & 0b1;
    return bit;
}

int getExponent(Number number)
{
    int power = 1;
    int exponent = 0;
    for (int i = 4; i < 8; i++) {
        exponent += power * getBit(number.binaryForm[6], i);
        power <<= 1;
    }
    for (int i = 0; i < 7; i++) {
        exponent += power * getBit(number.binaryForm[7], i);
        power <<= 1;
    }
    return exponent - 1024 + 1;
}

double getMantissa(Number number)
{
    double power = 0.5;
    double mantissa = 1;
    for (int i = 3; i >= 0; i--) {
        mantissa += power * getBit(number.binaryForm[6], i);
        power /= 2;
    }
    for (int j = 5; j >= 0; j--)
        for (int i = 7; i >= 0; i--) {
            mantissa += power * getBit(number.binaryForm[j], i);
            power /= 2;
        }
    return mantissa;
}

char getSign(Number number)
{
    if (getBit(number.binaryForm[7], 7))
        return '-';
    return '+';
}

int main()
{
    Number number;
    printf("Enter a number:");
    scanf("%lf", &number.value);
    printf("Result:  %c%g*2^%d", getSign(number), getMantissa(number), getExponent(number));
    return 0;
}