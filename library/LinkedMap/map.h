
#ifndef UNTITLED4_MAP_H
#define UNTITLED4_MAP_H

#include <stdbool.h>

typedef struct LinkedMapElement LinkedMapElement;
typedef struct LinkedMap LinkedMap;

LinkedMap* makeLinkedMap();
int get(LinkedMap *map, char* key);
void add(LinkedMap* map, char* key);
void put(LinkedMap *map, char* key, int value);
LinkedMapElement* find(LinkedMap* map, char* key);
bool hasKey(LinkedMap* map, char* key);
void fillLinkedMap(FILE* input, LinkedMap* linkedMap);
void printLinkedMap(FILE* output, LinkedMap* linkedMap);
void deleteLinkedmap(LinkedMap* linkedMap);

#endif //UNTITLED4_MAP_H
