#include "../library/LinkedMap/map.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE* input = fopen(argv[1], "r");
    if (!input)
        printf("incorrect path to the input file");
    else {
        LinkedMap* words = makeLinkedMap();
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
    }
    return 0;
}
