#include <stdio.h>
#include <stdlib.h>

int getQuotient(int divident, int divisor) {
    int quotient = 0;
    int absDivident = abs(divident);
    int absDivisor = abs(divisor);
    while (absDivident >= absDivisor) {
        absDivident = absDivident - absDivisor;
        quotient++;
    }
    if (divident < 0)
        quotient = -1 * quotient - 1;
    if (divisor < 0)
        quotient = -1 * quotient;
    return quotient;
}

int main()
{
    int divident = 0, divisor = 0;
    printf("Input 2 integer numbers \n");
    scanf("%d %d", &divident, &divisor);
    int quotient = getQuotient(divident, divisor);
    printf("Incomplete quotient of %d and %d: %d", divident, divisor, quotient);
    return 0;
}