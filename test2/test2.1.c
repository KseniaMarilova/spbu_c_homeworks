#include <stdio.h>

int getFibonacci(int number)
{
    int previous = 0;
    int current = 1;
    int buffer = 0;
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
    printf("%dth fibonacci number: %d", number, getFibonacci(number));
    return 0;
}
