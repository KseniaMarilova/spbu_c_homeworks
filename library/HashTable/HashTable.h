#ifndef HASHMAP_HASHTABLE_H
#define HASHMAP_HASHTABLE_H

#include "../ListOfValue/list.h"
#include <stdbool.h>
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
bool hashKeyInHashTable(HashTable* table, Value key);
HashTable* putToHashTable(HashTable* table, Value key, Value data);
Value getValueInHashTable(HashTable* table, Value key);
Pair removeKeyInHashTable(HashTable* table, Value key);
void deleteHashTable(HashTable* table);

typedef struct HashTableIterator{
    ListElement* pointer;
    HashTable* hashTable;
    int position;
} HashTableIterator;

HashTableIterator* getIterator(HashTable* table);
Pair getIteratorValue(HashTableIterator* iterator);
void next(HashTableIterator* iterator);

#endif //HASHMAP_HASHTABLE_H