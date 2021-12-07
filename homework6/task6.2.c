#include "../library/HashTable/HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareCoordinates(Value first, Value second)
{
    Pair* firstPair = getPointer(first);
    Pair* secondPair = getPointer(second);
    return !((getDouble(firstPair->key) == getDouble(secondPair->key)) && (getDouble(firstPair->data) == getDouble(secondPair->data)));
}

uint32_t hashFunction(Value key)
{
    Pair* coordinate = getPointer(key);
    double x = getDouble(coordinate->key);
    uint32_t x1 = 0;
    memcpy(&x1, &x, 4);
    double y = getDouble(coordinate->data);
    uint32_t y1 = 0;
    memcpy(&y1, &y, 4);
    return x1 ^ y1;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("wrong number of program arguments");
        return 0;
    }
    FILE* input = fopen(argv[1], "r");
    if (!input) {
        printf("incorrect path to the input file");
        return 0;
    }
    FILE* output = fopen(argv[2], "w");
    if (!output) {
        printf("incorrect path to the output file");
        return 0;
    }
    HashTable* table = createHashTable(compareCoordinates, hashFunction);
    char command[50] = "";
    double x = 0, y = 0;
    int index = 0;
    while (fscanf(input, "%s", command) != EOF) {
        if (!strcmp(command, "PUT")) {
            fscanf(input, "%lf", &x);
            fscanf(input, "%lf", &y);
            fscanf(input, "%d", &index);
            Pair* pair = malloc(sizeof(Pair));
            pair->key = wrapDouble(x);
            pair->data = wrapDouble(y);
            table = putToHashTable(table, wrapPointer(pair), wrapInt(index));
        }
        if (!strcmp(command, "GET")) {
            fscanf(input, "%lf", &x);
            fscanf(input, "%lf", &y);
            Pair* pair = malloc(sizeof(Pair));
            pair->key = wrapDouble(x);
            pair->data = wrapDouble(y);
            Value attempt = getValueInHashTable(table, wrapPointer(pair));
            if (isNone(attempt))
                printf("not found");
            else
                fprintf(output, "%d\n", getInt(attempt));
            free(pair);
        }
    }
    HashTableIterator* iterator = getIterator(table);
    while (iterator->pointer) {
        Pair pair = getIteratorValue(iterator);
        free(getPointer(pair.key));
        next(iterator);
    }
    free(iterator);
    deleteHashTable(table);
}