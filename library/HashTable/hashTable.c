#include "hashTable.h"
#include <stdio.h>
#include <stdlib.h>

HashTable* createHashTable(Comparator comparator, HashFunction hashfunction)
{
    HashTable* new = malloc(sizeof(HashTable));
    new->comparator = comparator;
    new->nBuckets = START_SIZE;
    new->bucket = malloc(new->nBuckets * sizeof(List));
    for (int i = 0; i < new->nBuckets; i++)
        new->bucket[i] = createList(comparator);
    return new;
}

int getLoadFactor(HashTable* table)
{
    return table->nElements / table->nBuckets;
}

bool hasHashKey(HashTable* table, Value key)
{
    int hash = hashFunction(key) % table->nBuckets;
    return hasKey(table->bucket[hash], key);
}

HashTable* moveToBig(HashTable* table);

void putHash(HashTable* table, Value key, Value data)
{
    int hash = hashFunction(key) % table->nBuckets;
    if (!hasKey(table->bucket[hash], key)) {
        table->nElements++;
        if (getLoadFactor(table) > LOAD_FACTOR) {
            HashTable *newTable = moveToBig(table);
            deleteHashTable(table);
            table = newTable;
        }
    }
    put(table->bucket[hash], key, data);
}

Value getHash(HashTable* table, Value key)
{
    int hash = hashFunction(key) % table->nBuckets;
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
    int hash = hashFunction(key) % table->nBuckets;
    Pair pair = removeKey(table->bucket[hash], key);
    return pair;
}

HashTableIterator* getIterator(HashTable* table)
{
    HashTableIterator* iterator = malloc(sizeof(HashTableIterator));
    iterator->hashTable = table;
    for (int i = 0; i < table->nBuckets; i++)
        if (table->bucket[i]->head) {
            iterator->pointer = table->bucket[i]->head;
            return iterator;
        }
    iterator->pointer = NULL;
    return iterator;
}

Pair getValue1(HashTableIterator* iterator)
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
    if (iterator->pointer->next)
        iterator->pointer = iterator->pointer->next;
    else
        for (int i = 0; i < iterator->hashTable->nBuckets; i++)
            if (iterator->hashTable->bucket[i]->head)
                iterator->pointer = iterator->hashTable->bucket[i]->head;
    iterator->pointer = NULL;
}

HashTable* moveToBig(HashTable* table)
{
    HashTable* new = malloc(sizeof(HashTable));
    new->nBuckets = table->nBuckets * 3;
    new->bucket = malloc(new->nBuckets * sizeof(List));
    for (int i = 0; i < new->nBuckets; i++)
        new->bucket[i] = createList(table->comparator);
    HashTableIterator* iterator = getIterator(table);
    while (iterator) {
        putHash(new, iterator->pointer->key, iterator->pointer->data);
        next(iterator);
    }
    return new;
}