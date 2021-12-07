#ifndef HASHMAP_LIST_H
#define HASHMAP_LIST_H

#include "Value/Value.h"
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
//наличие ключа
bool hasKey(List* list, Value key);
//добавление элемента в конец
void add(List* list, Value key, Value data);
//присвоить ключу дату, если ключа нет - добавить
void put(List* list, Value key, Value data);
//удаление элемента с таким ключом
Pair removeKey(List* list, Value key);
//получить дату этого ключа
Value getData(List* list, Value key);
//получить первый ключ с такой датой
Value getValue(List* list, Value data);
//ссылка на элемент с таким ключом
ListElement* findKey(List* list, Value key);
//void printList(List* list);

#endif //HASHMAP_LIST_H
