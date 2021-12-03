#include "list.h"
#include <stdio.h>
#include <stdlib.h>

ListElement* createListElement(Value key, Value data)
{
    ListElement* new = malloc(sizeof(ListElement));
    new->key = key;
    new->data = data;
    new->next = NULL;
    return new;
}

List* createList(Comparator comparator)
{
    List* new = malloc(sizeof(List));
    new->head = NULL;
    new->comparator = comparator;
    return new;
}

void deleteList(List* list)
{
    ListElement* next = NULL;
    for (ListElement* current = list->head; current; current = next) {
        next = current->next;
        free(current);
    }
    free(list);
}

void add(List* list, Value key, Value data)
{
    ListElement* new = createListElement(key, data);
    new->next = list->head;
    list->head = new;
}

ListElement* findKey(List* list, Value key)
{
    ListElement* current = list->head;
    for (ListElement* current = list->head; current; current = current->next) {
        if (!list->comparator(current->key, key))
            return current;
    }
    return NULL;
}

bool hasKey(List* list, Value key)
{
    return findKey(list, key);
}

void put(List* list, Value key, Value data)
{
    ListElement* element = findKey(list, key);
    if (element)
        element->data = data;
    else
        add(list, key, data);
}

Pair removeKey(List* list, Value key)
{
    Pair pair;
    if (!list->comparator(list->head->key, key)) {
        ListElement* temporary = list->head;
        list->head = list->head->next;
        pair.key = temporary->key;
        pair.data = temporary->data;
        free(temporary);
        return pair;
    }
    ListElement* current = list->head->next;
    for (ListElement* previous = list->head; previous->next; previous = previous->next) {
        ListElement* current = previous->next;
        if (!list->comparator(current->key, key)) {
            previous->next = current->next;
            pair.key = current->key;
            pair.data = current->data;
            free(current);
            return pair;
        }
    }
    pair.key = wrapNone();
    pair.data = wrapNone();
    return pair;
}

Value getData(List* list, Value key)
{
    ListElement* element = findKey(list, key);
    return element ? element->data : wrapNone();
}


