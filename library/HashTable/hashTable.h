#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../ListOfValue/list.h"
#include <stdbool.h>
#include <stdint.h>

#define START_SIZE 4
#define LOAD_FACTOR 1

typedef uint32_t (*HashFunction)(Value);

typedef struct HashTable{
    List** bucket;
    Comparator comparator;
    HashFunction hashfunction;
    int nBuckets;
    int nElements;
} HashTable;

HashTable* createHashTable(Comparator comparator, HashFunction hashfunction);
bool hasHashKey(HashTable* table, Value key);
void putHash(HashTable* table, Value key, Value data);
Value getHash(HashTable* table, Value key);
Pair removeHashKey(HashTable* table, Value key);
void deleteHashTable(HashTable* table);
int getSize(HashTable* table);

typedef struct HashTableIterator{
    ListElement* pointer;
    HashTable* hashTable;
} HashTableIterator;

HashTableIterator* getIterator(HashTable* table);
Pair getValue1(HashTableIterator* iterator);
void next(HashTableIterator* iterator);

#endif //HASHTABLE_H