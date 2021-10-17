#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

struct Range{
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

ListElement* createListElemet(char symbol)
{
    ListElement* new = malloc(sizeof(ListElement));
    new->symbol = symbol;
    new->next = NULL;
    return new;
}

void pushBack(List* line, char symbol)
{
    ListElement* new = createListElemet(symbol);
    if (line->head == NULL) {
        line->head = createListElemet(0);
        line->head->next = new;
        line->tail = new;
        return;
    }
    line->tail->next = new;
    line->tail = new;
}

Range* find(List* fragment, ListElement* start)
{
    ListElement* currentLineElement = start;
    for (ListElement* currentStart = start; currentStart->next; currentStart = currentStart->next) {
        ListElement* fragmentEnd = fragment->head;
        currentLineElement = currentStart;
        for (ListElement *currentFragmentElement = fragment->head; currentFragmentElement->next && currentLineElement->next; currentFragmentElement = currentFragmentElement->next) {
            if (currentFragmentElement->next->symbol != currentLineElement->next->symbol)
                break;
            currentLineElement = currentLineElement->next;
            fragmentEnd = fragmentEnd->next;
        }
        if (!fragmentEnd->next)
            return createRange(currentStart, currentLineElement);
    }
    return NULL;
}

void freeRangeOfList(Range* range)
{
    ListElement* next = NULL;
    for (ListElement* current = range->start->next; current != range->end; current  = next) {
        next = current->next;
        free(current);
    }
}

bool insert(List* list, List* start, List* fragment)
{
    Range* found = find(start, list->head);
    if (!found)
        return false;
    fragment->tail->next = found->end->next;
    found->end->next = fragment->head->next;
    free(found);
    return true;
}

bool delete(List* list, List* start, List* end)
{
    Range* foundStart = find(start, list->head);
    Range* foundEnd = find(end, foundStart->end);
    if (!(foundStart && foundEnd))
        return false;
    Range* r = createRange(foundStart->start, foundEnd->end);
    freeRangeOfList(r);
    foundStart->start->next = foundEnd->end->next;
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
    found->start->next = fragment->head->next;
    fragment->tail->next = found->end->next;
    free(found);
    return true;
}

void deleteList(List* list)
{
    ListElement* next = NULL;
    for (ListElement* current = list->head; current; current  = next) {
        next = current->next;
        free(current);
    }
    free(list);
}