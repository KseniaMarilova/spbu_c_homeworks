#include "map.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedMap* createLinkedMap()
{
    LinkedMap* map = malloc(sizeof(LinkedMap));
    map->head = NULL;
    return map;
}

LinkedMapElement* createLinkedMapElement(char* key, int value)
{
    LinkedMapElement* element = malloc(sizeof(LinkedMapElement));
    element->key = strdup(key);
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
    LinkedMapElement* element = find(map, key);
    if (element)
        element->value = value;
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
    LinkedMapElement* element = find(map, key);
    return element ? element->value : defaultValue;
}

bool hasKey(LinkedMap* map, char* key)
{
    return find(map, key);
}

void deleteLinkedmap(LinkedMap* linkedMap)
{
    if (linkedMap->head) {
        LinkedMapElement *previous = linkedMap->head;
        LinkedMapElement *current = linkedMap->head->nextElement;
        while (current) {
            free(previous->key);
            free(previous);
            previous = current;
            current = current->nextElement;
        }
        free(previous->key);
        free(previous);
    }
    free(linkedMap);
}