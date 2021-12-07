#include "HashTable.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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


int printList(List* list)
{
    int i = 0;
    for (ListElement* c = list->head; c; c = c->next) {
        Pair* pair = getPointer(c->key);
        printf("%f:%f %d;  ", getDouble(pair->key), getDouble(pair->data), getInt(c->data));
        i++;
    }
    return i;
}

double outputHashTable(HashTable* table)
{
    int max = 0;
    int cols = 0;
    for (int i = 0; i < table->nBuckets; i++) {
        printf("\n%d bucket ", i);
        int j = printList(table->bucket[i]);
        if (j > 1)
            cols++;
        if (j > max)
            max = j;
    }
    printf("max collisia: %d, n cols: %d, nElements: %d, quality: %f\n", max, cols, table->nElements, (double) cols / table->nBuckets);
    return (double) cols / table->nBuckets;
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
            table = putHash(table, wrapPointer(pair), wrapInt(index));
        }
        if (!strcmp(command, "GET")) {
            fscanf(input, "%lf", &x);
            fscanf(input, "%lf", &y);
            Pair* pair = malloc(sizeof(Pair));
            pair->key = wrapDouble(x);
            pair->data = wrapDouble(y);
            Value found = getHash(table, wrapPointer(pair));
            if (isNone(found))
                printf("not found");
            else
                fprintf(output, "%d\n", getInt(found));
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
