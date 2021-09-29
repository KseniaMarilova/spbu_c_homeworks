#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

int main(int argc, char* argv[])
{
    LinkedMap* words = makeLinkedMap();
    FILE* input = fopen(argv[1], "r") ;
    fillLinkedMap(input, words);
    fclose(input);
    FILE* output = fopen(argv[2], "w");
    printLinkedMap(output, words);
    fclose(output);
    deleteLinkedmap(words);
    return 0;
}
