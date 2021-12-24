#include <stdio.h>
#include <stdlib.h>

int function(int number)
{
    int* f = calloc(4, sizeof(int));
    int result = 0;
    f[0] = -1;
    f[1] = 0;
    f[2] = 1;
    if (number < 3)
        result =  f[number];
    else {
        for (int i = 2; i < number; i++) {
            f[3] = f[0] * 3 + f[1] * 2 + f[2];
            for (int j = 0; j < 3; j++)
                f[j] = f[j + 1];
        }
        result = f[2];
    }
    free(f);
    return result;
}

int main()
{
    int number = 0;
    printf("input number:\n");
    scanf("%d", &number);
    printf("f(%d) = %d ", number, function(number));
    return 0;
}