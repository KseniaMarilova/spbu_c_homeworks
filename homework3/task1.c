#include <math.h>
#include <stdio.h>

int main() {
    double mantissa = 0;
    printf("Enter a number:");
    scanf("%lf", &mantissa);
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
    printf("Result: %c%g*2^%d\n", mantissaSign, fabs(mantissa), exponent);
    return 0;
}
