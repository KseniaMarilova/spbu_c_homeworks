#include <math.h>
#include <stdio.h>

typedef struct Complex {
    double re;
    double im;
} Complex;

Complex add(Complex a, Complex b)
{
    Complex result;
    result.re = a.re + b.re;
    result.im = a.im + b.im;
    return result;
}

Complex substract(Complex a, Complex b)
{
    Complex result;
    result.re = a.re + b.re;
    result.im = a.im + b.im;
    return result;
}

Complex multiply(Complex a, Complex b)
{
    Complex result;
    result.re = a.re * b.re - a.im * b.im;
    result.im = a.re * b.im + a.im * b.re;
    return result;
}

Complex divide(Complex a, Complex b)
{
    Complex result;
    double conjugate = b.re * b.re + b.im * b.im;
    result.re = (a.re * b.re + a.im * b.im) / conjugate;
    result.im = (a.im * b.re - a.re * b.im) / conjugate;
    return result;
}

double modul(Complex a)
{
    return sqrt(a.re * a.re + a.im * a.im);
}

void printComplex(Complex a)
{
    if (a.re)
        printf("%lf", a.re);
    if (a.re && a.im < 0)
        printf("+", a.re, a.im);
    if (a.im)
        printf("%lf", a.im);
}

int main()
{
    Complex firstNumber, secondNumber;
    firstNumber.re = 0;
    firstNumber.im = 0;
    secondNumber.re = 0;
    secondNumber.im = 0;
    printf("input real part of fist number:\n");
    scanf("%lf", &firstNumber.re);
    printf("input imaginary part of fist number:\n");
    scanf("%lf", &firstNumber.im);
    printf("input real part of second number:\n");
    scanf("%lf", &secondNumber.re);
    printf("input imaginary part of second number:\n");
    scanf("%lf", &secondNumber.im);
    printf("first number:");
    printComplex(firstNumber);
    printf("\nsecond number:");
    printComplex(secondNumber);
    printf("\nsum of numbers: ");
    printComplex(add(firstNumber, secondNumber));
    printf("\ndifference product of numbers: ");
    printComplex(substract(firstNumber, secondNumber));
    printf("\nproduct of numbers: ");
    printComplex(multiply(firstNumber, secondNumber));
    printf("\nquotient of numbers: ");
    printComplex(divide(firstNumber, secondNumber));
    printf("\nmodul of first numbers: %lf", modul(firstNumber));
    return 0;
}
