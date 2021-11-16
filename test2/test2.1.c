#include <stdio.h>

long long getFibonacci(int number)
{
    long long previous = 0;
    long long current = 1;
    long long buffer = 0;
    for (int i = 2; i < number; i++) {
        buffer = current;
        current = current + previous;
        previous = buffer;
    }
    return current;
}

int main()
{
    printf("enter the number of the fibonacci");
    int number = 0;
    scanf("%d", &number);
    if (number < 0 || number > 90)
        printf("wrong input");
    else
        printf("%ld fibonacci number: %d", number, getFibonacci(number));
    return 0;
}
