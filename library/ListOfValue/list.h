#ifndef LIST_H
#define LIST_H

#include "../Value/Value.h"
#include <stdbool.h>

typedef struct List List;
typedef struct ListElement ListElement;
typedef struct Pair Pair;

struct ListElement{
    Value key;
    Value data;
    ListElement* next;
};
struct List{
    ListElement* head;
    Comparator comparator;
    int size;
};
struct Pair{
    Value key;
    Value data;
};
List* createList(Comparator comparator);
void deleteList(List* list);
bool hasKey(List* list, Value key);
void add(List* list, Value key, Value data);
void put(List* list, Value key, Value data);
Pair removeKey(List* list, Value key);
Value getData(List* list, Value key);
Value getValue(List* list, Value data);
ListElement* findKey(List* list, Value key);

#endif //LIST_H