
#ifndef SPBU_C_HOMEWORKS_HEAP_H
#define SPBU_C_HOMEWORKS_HEAP_H

#include <stdlib.h>

typedef struct Pair Pair;
typedef struct Heap Heap;

struct Pair {
    int first;
    int second;
};

struct Heap{
    Pair* list;
    int size;
};

Heap* createHeap(int maxSize);
void insert(Heap* heap, Pair pair);
Pair extractMin(Heap* heap);
void deleteHeap(Heap* heap);

#endif // SPBU_C_HOMEWORKS_HEAP_H
