#include <stdio.h>
#include <stdbool.h>
#include <math.h>

typedef struct Vector Vector;

struct Vector {
    int* element;
    int size;
};

Vector* createVector(int size)
{
    Vector* newVector = malloc(sizeof(Vector));
    newVector->element = calloc(size, sizeof(int));
    newVector->size = size;
    return newVector;
}

bool checkSizes(Vector* a, Vector* b)
{
    return a->size == b->size;
}
bool scalarProduct(Vector* a, Vector* b, int* result)
{
    if (!checkSizes(a, b))
        return false;
    *result = 0;
    for (int i = 0; i < a->size; i++)
        *result = *result + a->element[i] * b->element[i];
    return true;

}

Vector* addition(Vector* first, Vector* second)
{
    if (!checkSizes(first, second))
        return NULL;
    Vector* result = createVector(first->size);
    for( int i = 0; i < first->size; i++) {
        result->element[i] = first->element[i] + second->element[i];
    }
    return result;

}


void printVector(Vector* a) {
    for(int i = 0; i < a->size; i++)
        printf("%d ", a->element[i]);
    printf("\n");
}

Vector* readVector() {
    int size;
    printf("input size of vector\n");
    scanf("%d", &size);
    printf("input vector\n");
    Vector* a = createVector(size);
    int x;
    for (int i =0; i<size; i++) {
        scanf("%d", &x);
        a->element[i] = x;
    }
    return a;
}
int main() {
    Vector* first = readVector();
    Vector* second = readVector();
    printf("first vector:\n");
    printVector(first);
    printf("second vector:\n");
    printVector(second);
    int product = 0;
    if (scalarProduct(first, second, &product)) {
        printf("scalar product of vectors: \n");
        printf("%d", product);
        printf("\n");
    }
    else
        printf("can't get scalar product: vectors have different sizes");
    Vector* sum = addition(first, second);
    if (sum) {
        printf("sum of vectors:\n");
        printVector(sum);
        printf("\n");
    }
    else
        printf("can't sum: vectors have different sizes");
    return 0;

}
