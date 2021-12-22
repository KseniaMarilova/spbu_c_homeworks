#include "list.h"
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

bool put(List* list, Value key, Value data)
{
    ListElement* element = findKey(list, key);
    if (element) {
        element->data = data;
        return true;
    }
    add(list, key, data);
    return false;
}

Pair removeKey(List* list, Value key)
{
    ListElement* previous = NULL;
    for (ListElement* current = list->head; current; current = current->next) {
        if (!list->comparator(current->key, key)) {
            if (previous)
                previous->next = current->next;
            else
                list->head = current->next;
            Pair pair = { current->key, current->data };
            free(current);
            return pair;
        }
        previous = current;
    }
    Pair pair = { wrapNone(), wrapNone() };
    return pair;
}

Value get(List* list, Value key)
{
    ListElement* element = findKey(list, key);
    return element ? element->data : wrapNone();
}