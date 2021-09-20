#include <stdio.h>
#include <stdlib.h>
int main()
{
    printf("Input 2 integer numbers a, b \n");
    int a = 0, b = 0;
    scanf("%d%d", &a, &b);
    int r = 0;
    int absA = abs(a);
    int absB = abs(b);
    while (absA >= absB) {
        absA = absA - absB;
        r++;
    }
    if (a < 0)
        r = -1 * r - 1;
    if (b < 0)
        r = -1 * r;
    printf("Incomplete quotient of a, b: %d", r);
}