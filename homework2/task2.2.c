#include "../library/ListOfChar/list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void modifyDna(char* command, List* list, List* argument1, List* argument2)
{
    if (!strcmp("DELETE", command)) {
        if (!delete (list, argument1, argument2))
            printf("deletion error");
    } else if (!strcmp("INSERT", command)) {
        if (!insert(list, argument1, argument2))
            printf("insert error");
    } else if (!strcmp("REPLACE", command)) {
        if (!replace(list, argument1, argument2))
            printf("replace error");
    } else
        printf("incorrect command");
}

void printDna(FILE* output, List* line)
{
    for (ListElement* current = line->head->next; current; current = current->next)
        fprintf(output, "%c", current->symbol);
    fprintf(output, "\n");
}

List* readDna(FILE* input)
{
    List* list = createList();
    char symbol[129] = "";
    fscanf(input, "%s", symbol);
    for (int i = 0; symbol[i] != '\0'; i++)
        pushBack(list, symbol[i]);
    return list;
}

int main(int argc, char* argv[])
{
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    if (argc != 3) {
        printf("wrong number of program arguments");
        return 0;
    }
    if (!input) {
        printf("incorrect path to the input file");
        return 0;
    }
    if (!output) {
        printf("incorrect path to the output file");
        close(input);
        return 0;
    }
    int n = 0;
    fscanf(input, "%d", &n);
    List* dnaList = readDna(input);
    int m = 0;
    fscanf(input, "%d", &m);
    for (int i = 0; i < m; i++) {
        char command[10] = "";
        fscanf(input, "%s", command);
        List* argument1 = readDna(input);
        List* argument2 = readDna(input);
        modifyDna(command, dnaList, argument1, argument2);
        printDna(output, dnaList);
        deleteList(argument1);
        deleteList(argument2);
    }
    deleteList(dnaList);
    fclose(input);
    fclose(output);
    return 0;
}