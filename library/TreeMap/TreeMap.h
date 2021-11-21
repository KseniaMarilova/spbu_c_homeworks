#ifndef AVLTREES_AVLTREE_H
#define AVLTREES_AVLTREE_H

#include "../Value/Value.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct TreeMap TreeMap;
typedef struct TreeMapIterator TreeMapIterator;

struct TreeMap {
    ValueType keyType;
    ValueType dataType;
    Node* root;
};

TreeMap* createTreeMap(ValueType keyType, ValueType dataType);
void deleteTreeMap(TreeMap* map);
void put(TreeMap* map, Value key, Value data);
void removeKey(TreeMap* map, Value key);
Value get(Node* node, Value key);
bool hasKey(TreeMap* map, Value key);
Value getLowerBound(TreeMap* map, Value key);
Value getUpperBound(TreeMap* map, Value key);
Value getMaximum(TreeMap* map);
Value getMinimum(TreeMap* map);

TreeMapIterator* getIterator(TreeMap* map);
Value getKey(TreeMapIterator* iterator);
Value getValue(TreeMapIterator* iterator);
void next(TreeMapIterator* iterator);
bool hasElement(TreeMapIterator* iterator);

#endif //AVLTREES_AVLTREE_H
