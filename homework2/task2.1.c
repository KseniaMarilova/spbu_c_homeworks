#include "../library/LinkedMap/map.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fillLinkedMap(FILE* input, LinkedMap* linkedMap)
{
    char key[128];
    while (fscanf(input, "%s", key) != EOF)
        put(linkedMap, key, get(linkedMap, key, 0) + 1);
}

void printLinkedMap(FILE* output, LinkedMap* linkedMap)
{

    LinkedMapElement* currentElement = linkedMap->head;
    while (currentElement) {
        fprintf(output, "%s,%d\n", currentElement->key, currentElement->value);
        currentElement = currentElement->nextElement;
    }
}

int main(int argc, char* argv[])
{
    FILE* input = fopen(argv[1], "r");
    if (argc != 3) {
        printf("wrong number of program arguments");
        return 0;
    }
    if (!input) {
        printf("incorrect path to the input file");
        return 0;
    }
    LinkedMap* words = createLinkedMap();
    fillLinkedMap(input, words);
    fclose(input);
    FILE* output = fopen(argv[2], "w");
    if (!output)
        printf("incorrect path to the output file");
    else {
        printLinkedMap(output, words);
        fclose(output);
    }
    deleteLinkedmap(words);
    return 0;
}