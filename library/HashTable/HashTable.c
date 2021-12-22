#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
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
    return (double)(table->nElements / table->nBuckets);
}

bool hashKeyInHashTable(HashTable* table, Value key)
{
    int hash = table->hashFunction(key) % table->nBuckets;
    return hasKey(table->bucket[hash], key);
}

void moveToBig(HashTable* table);

void putToHashTable(HashTable* table, Value key, Value data)
{
    if (getLoadFactor(table) >= LOAD_FACTOR)
        moveToBig(table);
    int hash = table->hashFunction(key) % table->nBuckets;
    if (!put(table->bucket[hash], key, data))
        table->nElements++;
}

Value getValueInHashTable(HashTable* table, Value key)
{
    int hash = table->hashFunction(key) % table->nBuckets;
    return get(table->bucket[hash], key);
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
    table->nElements--;
    return pair;
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
    if (iterator && iterator->pointer) {
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
    }
    for (int i = iterator->position + 1; i < iterator->hashTable->nBuckets; i++) {
        if (iterator->hashTable->bucket[i]->head) {
            iterator->pointer = iterator->hashTable->bucket[i]->head;
            iterator->position = i;
            return;
        }
    }
    iterator->pointer = NULL;
}

void moveToBig(HashTable* table)
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
    free(iterator);
    for (int i = 0; i < table->nBuckets; i++)
        deleteList(table->bucket[i]);
    table->bucket = new->bucket;
    table->nBuckets = new->nBuckets;
    table->nElements = new->nElements;
    free(new);
}