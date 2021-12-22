#ifndef UNTITLED7_LIST_H
#define UNTITLED7_LIST_H

#include <stdbool.h>

typedef struct ListElement ListElement;
typedef struct List List;
typedef struct Range Range;

struct ListElement{
    char symbol;
    ListElement* next;
};

struct List{
    ListElement* head;
    ListElement* tail;
};

List* createList();
void pushBack(List* line, char symbol);
bool insert(List* line, List* start, List* fragment);
bool replace(List* line, List* template, List* fragment);
bool delete(List* list, List* start, List* end);
void deleteList(List* list);

#endif //UNTITLED7_LIST_H
