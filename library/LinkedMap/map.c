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
};

LinkedMap* createLinkedMap()
{
    LinkedMap* map = malloc(sizeof(LinkedMap));
    map->head = NULL;
    return map;
}

LinkedMapElement* createLinkedMapElement(char* key, int value)
{
    LinkedMapElement* element = malloc(sizeof(LinkedMapElement));
    strcpy(element->key, key);
    element->value = value;
    element->nextElement = NULL;
    return element;
}

void add(LinkedMap* map, char* key)
{
    LinkedMapElement* newElement = createLinkedMapElement(key, 1);
    newElement->nextElement = map->head;
    map->head = newElement;
}

void put(LinkedMap* map, char* key, int value)
{
    LinkedMapElement* e = find(map, key);
    if (e)
        e->value = value;
    else
        add(map, key);
}

LinkedMapElement* find(LinkedMap* map, char* key)
{
    LinkedMapElement* current = map->head;
    for (LinkedMapElement* current = map->head; current; current = current->nextElement) {
        if (!strcmp(current->key, key))
            return current;
    }
    return NULL;
}

int get(LinkedMap* map, char* key, int defaultValue)
{
    LinkedMapElement* e = find(map, key);
    return e ? e->value : defaultValue;
}

bool hasKey(LinkedMap* map, char* key)
{
    return find(map, key);
}

void deleteLinkedmap(LinkedMap* linkedMap)
{
    if (linkedMap->head) {
        LinkedMapElement* previous = linkedMap->head;
        LinkedMapElement* current = linkedMap->head->nextElement;
        while (current) {
            free(previous);
            previous = current;
            current = current->nextElement;
        }
        free(previous);
    }
    free(linkedMap);
}