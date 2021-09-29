#include "map.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LinkedMapElement {
    char key[128];
    int value;
    LinkedMapElement* nextElement;
};

struct LinkedMap {
    LinkedMapElement* head;
    LinkedMapElement* tail;
};

LinkedMap* makeLinkedMap()
{
    LinkedMap* map = malloc(sizeof(LinkedMap));
    map->head = NULL;
    return map;
}

LinkedMapElement* makeLinkedMapElement(char* key)
{
    LinkedMapElement* element = malloc(sizeof(LinkedMapElement));
    strcpy(element->key, key);
    element->value = 1;
    element->nextElement = NULL;
    return element;
}

void add(LinkedMap* map, char* key)
{
    LinkedMapElement* newElement = makeLinkedMapElement(key);
    if (map->head == NULL)
        map->head = newElement;
    else {
        newElement->nextElement = map->head;
        map->head = newElement;
    }
}

void put(LinkedMap* map, char* key, int value)
{
    if (!hasKey(map, key))
        add(map, key);
    find(map, key)->value = value;
    return;
}

LinkedMapElement* find(LinkedMap* map, char* key)
{
    LinkedMapElement* currentElement = map->head;
    while (currentElement != NULL) {
        if (!strcmp(currentElement->key, key))
            return currentElement;
        currentElement = currentElement->nextElement;
    }
    return NULL;
}

int get(LinkedMap* map, char* key)
{
    if (hasKey(map, key))
        return find(map, key)->value;
    else
        return 0;
}

bool hasKey(LinkedMap* map, char* key)
{
    return find(map, key);
}

void fillLinkedMap(FILE* input, LinkedMap* linkedMap)
{
    while (!feof(input)) {
        char key[128];
        fscanf(input, "%s", key);
        put(linkedMap, key, get(linkedMap, key) + 1);
    }
    return;
}

void printLinkedMap(FILE* output, LinkedMap* linkedMap)
{
    LinkedMapElement* currentElement = linkedMap->head;
    while (currentElement != NULL) {
        fprintf(output, "%s,%d\n", currentElement->key, currentElement->value);
        currentElement = currentElement->nextElement;
    }
    return;
}

void deleteLinkedmap(LinkedMap* linkedMap)
{
    LinkedMapElement* previous = linkedMap->head;
    LinkedMapElement* current = linkedMap->head->nextElement;
    while (current != NULL) {
        free(previous);
        previous = current;
        current = current->nextElement;
    }
    free(previous);
    free(linkedMap);
    return;
}