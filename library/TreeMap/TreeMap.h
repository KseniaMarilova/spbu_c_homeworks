#ifndef AVLTREES_AVLTREE_H
#define AVLTREES_AVLTREE_H

#include "../Value/Value.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeMap TreeMap;
typedef struct Node Node;
typedef struct TreeMapIterator TreeMapIterator;

struct Node {
    Value key;
    Value data;
    int height;
    Node* leftChild;
    Node* rightChild;
} ;

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


#endif //AVLTREES_AVLTREE_H
