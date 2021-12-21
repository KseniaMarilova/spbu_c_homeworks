#include "heap.h"

Heap* createHeap(int maxSize)
{
    Heap* new = malloc(sizeof(Heap));
    new->list = malloc(sizeof(Pair) * maxSize);
    new->size = 0;
    return new;
}

void heapify(Heap* heap, int root)
{
    while (2 * root + 2 < heap->size) {
        int right = 2 * root + 1;
        int left = 2 * root + 2;
        int minChild = right;
        if (heap->list[right].first > heap->list[left].first)
            minChild = left;
        if (heap->list[minChild].first < heap->list[root].first) {
            Pair temp = heap->list[minChild];
            heap->list[minChild] = heap->list[root];
            heap->list[root] = temp;
        } else
            return;
        root = minChild;
    }
}

void insert(Heap* heap, Pair pair)
{
    heap->list[heap->size] = pair;
    for (int i = heap->size; i > 0 && heap->list[(i - 1) / 2].first > heap->list[i].first; i = (i - 1) / 2) {
        Pair temp = heap->list[(i - 1) / 2];
        heap->list[(i - 1) / 2] = heap->list[i];
        heap->list[i] = temp;
    }
    heap->size++;
}

Pair extractMin(Heap* heap)
{
    if (heap->size > 0) {
        Pair min = heap->list[0];
        heap->list[0] = heap->list[heap->size - 1];
        heap->size--;
        heapify(heap, 0);
        return min;
    }
}

void deleteHeap(Heap* heap)
{
    free(heap->list);
    free(heap);
}