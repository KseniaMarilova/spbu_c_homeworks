#include "HashTable.h"
#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


HashTable* createHashTable(Comparator comparator, HashFunction hashFunction)
{
    HashTable* new = malloc(sizeof(HashTable));
    new->comparator = comparator;
    new->hashFunction = hashFunction;
    new->nBuckets = START_SIZE;
    new->nElements = 0;
    new->bucket = malloc(new->nBuckets * sizeof(List*));
    for (int i = 0; i < new->nBuckets; i++)
        new->bucket[i] = createList(comparator);
    return new;
}

double getLoadFactor(HashTable* table)
{
   // printf("load factor %d\n", table->nElements / table->nBuckets);
    return (double) table->nElements / (double) table->nBuckets;
}

bool hasHashKey(HashTable* table, Value key)
{
    int hash = table->hashFunction(key) % table->nBuckets;
    return hasKey(table->bucket[hash], key);
}

HashTable* moveToBig(HashTable* table);

HashTable* putHash(HashTable* table, Value key, Value data)
{
    if (getLoadFactor(table) >= LOAD_FACTOR)
        table = moveToBig(table);
 //   printf("put: nbuckets: %d, key: %d\n", table->nBuckets, getInt(key));
    int hash = table->hashFunction(key) % table->nBuckets;
    if (!hasKey(table->bucket[hash], key))
        table->nElements++;
    else
        printf("alredy is");
    put(table->bucket[hash], key, data);
    return table;
}

Value getHash(HashTable* table, Value key)
{
    int hash = table->hashFunction(key) % table->nBuckets;
    return getData(table->bucket[hash], key);
}

void deleteHashTable(HashTable* table)
{
    for (int i = 0; i < table->nBuckets; i++)
        deleteList(table->bucket[i]);
    free(table->bucket);
    free(table);
}

Pair removeHashKey(HashTable* table, Value key)
{
    int hash = table->hashFunction(key) % table->nBuckets;
    Pair pair = removeKey(table->bucket[hash], key);
    return pair ;
}

HashTableIterator* getIterator(HashTable* table)
{
    HashTableIterator* iterator = malloc(sizeof(HashTableIterator));
    iterator->hashTable = table;
    iterator->position = 0;
    for (int i = 0; i < table->nBuckets; i++)
        if (table->bucket[i]->head) {
            iterator->pointer = table->bucket[i]->head;
            iterator->position = i;
            return iterator;
        }
    iterator->pointer = NULL;
    return iterator;
}

Pair getIteratorValue(HashTableIterator* iterator)
{
    Pair pair;
    if (iterator) {
        pair.key = iterator->pointer->key;
        pair.data = iterator->pointer->data;
    } else {
        pair.key = wrapNone();
        pair.data = wrapNone();
    }
    return pair;
}

void next(HashTableIterator* iterator)
{
    if (iterator->pointer->next) {
        iterator->pointer = iterator->pointer->next;
        return;
    } else
        for (int i = iterator->position + 1; i < iterator->hashTable->nBuckets; i++)
            if (iterator->hashTable->bucket[i]->head) {
                iterator->pointer = iterator->hashTable->bucket[i]->head;
                iterator->position = i;
                return;
            }
    iterator->pointer = NULL;
}

HashTable* moveToBig(HashTable* table)
{
    HashTable* new = malloc(sizeof(HashTable));
    new->nBuckets = table->nBuckets * 3;
    new->nElements = 0;
    new->bucket = malloc(new->nBuckets * sizeof(List*));
    new->hashFunction = table->hashFunction;
    new->comparator = table->comparator;
    for (int i = 0; i < new->nBuckets; i++)
        new->bucket[i] = createList(table->comparator);
    HashTableIterator* iterator = getIterator(table);
    while (iterator->pointer) {
        int hash = new->hashFunction(iterator->pointer->key) % new->nBuckets;
        new->nElements++;
        put(new->bucket[hash], iterator->pointer->key, iterator->pointer->data);
        next(iterator);
    }
    deleteHashTable(table);
    return new;
}

