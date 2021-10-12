#include <math.h>
#include <stdio.h>

void printNormalizedForm(double number)
{
    double mantissa = number;
    int exponent = 0;
    while (fabs(mantissa) < 1) {
        mantissa *= 2;
        exponent--;
    }
    while (fabs(mantissa) > 2) {
        mantissa /= 2;
        exponent++;
    }
    char mantissaSign = '+';
    if (mantissa < 0)
        mantissaSign = '-';
    printf("%c%g*2^%d", mantissaSign, fabs(mantissa), exponent);
}

int main()
{
    double number = 0;
    printf("Enter a number:");
    scanf("%lf", &number);
    printf("Result: ");
    printNormalizedForm(number);
    return 0;
}
