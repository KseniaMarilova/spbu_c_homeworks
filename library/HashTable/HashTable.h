#ifndef HASHMAP_HASHTABLE_H
#define HASHMAP_HASHTABLE_H

#include <stdbool.h>
#include "list.h"
#include <stdint.h>

#define START_SIZE 32
#define LOAD_FACTOR 1

typedef uint32_t (*HashFunction)(Value);

typedef struct HashTable{
    List** bucket;
    Comparator comparator;
    HashFunction hashFunction;
    int nBuckets;
    int nElements;
} HashTable;

HashTable* createHashTable(Comparator comparator, HashFunction hashfunction);
bool hasHashKey(HashTable* table, Value key);
HashTable* putHash(HashTable* table, Value key, Value data);
Value getHash(HashTable* table, Value key);
Pair removeHashKey(HashTable* table, Value key);
void deleteHashTable(HashTable* table);
int getSize(HashTable* table);

typedef struct HashTableIterator{
    ListElement* pointer;
    HashTable* hashTable;
    int position;
} HashTableIterator;

HashTableIterator* getIterator(HashTable* table);
Pair getIteratorValue(HashTableIterator* iterator);
void next(HashTableIterator* iterator);

#endif //HASHMAP_HASHTABLE_H
