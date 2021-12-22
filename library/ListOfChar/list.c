#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

struct Range {
    ListElement* start;
    ListElement* end;
};

Range* createRange(ListElement* start, ListElement* end)
{
    Range* new = malloc(sizeof(Range));
    new->start = start;
    new->end = end;
    return new;
}

List* createList()
{
    List* new = malloc(sizeof(List));
    new->head = NULL;
    new->tail = NULL;
    return new;
};

ListElement* createListElement(char symbol)
{
    ListElement* new = malloc(sizeof(ListElement));
    new->symbol = symbol;
    new->next = NULL;
    return new;
}

void pushBack(List* line, char symbol)
{
    ListElement* new = createListElement(symbol);
    if (line->head == NULL) {
        line->head = createListElement(0);
        line->head->next = new;
        line->tail = new;
        return;
    }
    line->tail->next = new;
    line->tail = new;
}

Range* find(List* fragment, ListElement* start)
{
    for (ListElement* currentStart = start; currentStart->next; currentStart = currentStart->next) {
        ListElement* fragmentPointer = fragment->head;
        ListElement* listPointer = currentStart;
        while (fragmentPointer->next && listPointer->next) {
            if (fragmentPointer->next->symbol != listPointer->next->symbol)
                break;
            fragmentPointer = fragmentPointer->next;
            listPointer = listPointer->next;
        }
        if (!fragmentPointer->next)
            return createRange(currentStart, listPointer);
    }
    return NULL;
}

void freeRangeOfList(Range* range)
{
    ListElement* next = NULL;
    for (ListElement* current = range->start->next; current != range->end; current = next) {
        next = current->next;
        free(current);
    }
}

bool insert(List* list, List* start, List* fragment)
{
    Range* found = find(start, list->head);
    if (!found)
        return false;
    ListElement* previous = found->end;
    ListElement* end = found->end->next;
    for (ListElement* pointer = fragment->head->next; pointer; pointer = pointer->next) {
        ListElement* current = createListElement(pointer->symbol);
        previous->next = current;
        previous = current;
    }
    previous->next = end;
    if (list->tail == found->end)
        list->tail = previous;
    free(found);
    return true;
}

bool delete (List* list, List* start, List* end)
{
    Range* foundStart = find(start, list->head);
    if (!foundStart)
        return false;
    Range* foundEnd = find(end, foundStart->end);
    if (!foundEnd) {
        free(foundStart);
        return false;
    }
    Range* r = createRange(foundStart->start, foundEnd->end);
    freeRangeOfList(r);
    free(r);
    if (list->tail == foundEnd->end)
        list->tail = foundStart->start;
    foundStart->start->next = foundEnd->end->next;
    free(foundEnd->end);
    free(foundStart);
    free(foundEnd);
    return true;
}

bool replace(List* list, List* template, List* fragment)
{
    Range* found = find(template, list->head);
    if (!found)
        return false;
    freeRangeOfList(found);
    ListElement* previous = found->start;
    for (ListElement* pointer = fragment->head->next; pointer; pointer = pointer->next) {
        ListElement* current = createListElement(pointer->symbol);
        previous->next = current;
        previous = current;
    }
    previous->next = found->end->next;
    if (!found->end->next)
        list->tail = previous;
    free(found->end);
    free(found);
    return true;
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