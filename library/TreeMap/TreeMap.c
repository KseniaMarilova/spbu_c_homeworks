#include "../Value/Value.h"
#include "TreeMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


TreeMap* createTreeMap(ValueType keyType, ValueType dataType)
{
    TreeMap* new = malloc(sizeof(TreeMap));
    new->root = NULL;
    new->dataType = dataType;
    new->keyType = keyType;
    return new;
};

Node* createNode(Value data, Value key)
{
    Node* new = malloc(sizeof(Node));
    new->data = data;
    new->key = key;
    new->leftChild = NULL;
    new->rightChild = NULL;
    new->height = 1;
    return new;
}

void freeNode(Node* root)
{
    if (root) {
        freeNode(root->leftChild);
        freeNode(root->rightChild);
    }
    free(root);
}

void deleteTreeMap(TreeMap* map)
{
    freeNode(map->root);
    free(map);
}

int getHeight(Node* node)
{
    return node ? node->height : 0;
}

int maxA(int a, int b)
{
    return a > b ? a : b;
}

void updateHeight(Node* node){
    if (node)
        node->height = maxA(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
}

int getBalanceFactor(Node* node)
{
    return node ? getHeight(node->rightChild) - getHeight(node->leftChild) : 0;
}

Node* rotateRight(Node* root)
{
    Node* child = root->leftChild;
    root->leftChild = child->rightChild;
    child->rightChild = root;
    updateHeight(root);
    updateHeight(child);
    return child;
}

Node* rotateLeft(Node* root)
{
    Node* child = root->rightChild;
    root->rightChild = child->leftChild;
    child->leftChild = root;
    updateHeight(root);
    updateHeight(child);
    return child;
}

Node* balance(Node* root)
{
    if (getBalanceFactor(root) == 2)
    {
        if (getBalanceFactor(root->rightChild) == -1)
            root->rightChild = rotateRight(root->rightChild);
        return rotateLeft(root);
    }
    if (getBalanceFactor(root) == -2)
    {
        if (getBalanceFactor(root->leftChild) == 1)
            root->leftChild = rotateLeft(root->leftChild);
        return rotateRight(root);
    }
    return root;
}

Node* insert(Node* root, Value key, Value data)
{
    if (!root)
        return createNode(data, key);
    if (compare(root->key, key) > 0)
        root->leftChild = insert(root->leftChild, key, data);
    else if (compare(root->key, key) < 0)
        root->rightChild = insert(root->rightChild, key, data);
    else
        root->data = data;
    updateHeight(root);
    root = balance(root);
    return root;
}

void put(TreeMap* map, Value key, Value data)
{
    if (map->keyType == key.type && map->dataType == data.type)
        map->root = insert(map->root, key, data);
    else
        printf("wrong types");
}

typedef struct Pair {
    Node* first;
    Node* second;
} Pair;

Pair makePair(Node* first, Node* second)
{
    return (Pair) { first, second };
}

Pair extractMax(Node* root)
{
    if (root->rightChild) {
        Pair pair = extractMax(root->rightChild);
        root->rightChild = pair.second;
        return makePair(pair.first, root);
    }
    return makePair(root, root->leftChild);
}

Node* removeNode(Node* root, Value key)
{
    if (!root)
        return NULL;
    if (compare(root->key, key) > 0) {
        root->leftChild = removeNode(root->leftChild, key);
        updateHeight(root);
        root = balance(root);
        return root;
    } else if (compare(root->key, key) < 0) {
        root->rightChild = removeNode(root->rightChild, key);
        updateHeight(root);
        root = balance(root);
        return root;
    }
    Node* newRoot = NULL;
    if (!root->leftChild)
        newRoot = root->rightChild;
    else if (!root->rightChild)
        newRoot = root->leftChild;
    else {
        Pair pair = extractMax(root->leftChild);
        newRoot = pair.first;
        newRoot->leftChild = pair.second;
        newRoot->rightChild = root->rightChild;
    }
    free(root);
    updateHeight(newRoot);
    newRoot = balance(newRoot);
    return newRoot;
}

void removeKey(TreeMap* map, Value key)
{
    map->root = removeNode(map->root, key);
}

Value get(Node* root, Value key)
{
    if (!root)
        return wrapNone();
    if (compare(root->key, key) > 0)
        return get(root->leftChild, key);
    else if (compare(root->key, key) < 0)
        return get(root->rightChild, key);
    else
        return root->data;
}

bool hasKey(TreeMap* map, Value key)
{
    return isNone(get(map->root, key));
}

Value getLowerBound(TreeMap* map, Value key)
{
    Node* previous = NULL;
    Node* current = map->root;
    while (current) {
        if (compare(current->key, key) < 0)
            current = current->rightChild;
        else {
            previous = current;
            current = current->leftChild;
        }
    }
    return previous ? previous->key : wrapNone();
}

Value getUpperBound(TreeMap* map, Value key)
{
    Node* previous = NULL;
    Node* current = map->root;
    while (current) {
        if (compare(current->key, key) <= 0)
            current = current->rightChild;
        else {
            previous = current;
            current = current->leftChild;
        }
    }
    return previous ? previous->key : wrapNone();

}

Value getMaximum(TreeMap* map)
{
    if (!map->root)
        return wrapNone();
    Node* current = map->root;
    while (current->rightChild)
        current = current->rightChild;
    return current->key;
}

Value getMinimum(TreeMap* map)
{
    if (!map->root)
        return wrapNone();
    Node* current = map->root;
    while (current->leftChild)
        current = current->leftChild;
    return current->key;
}
