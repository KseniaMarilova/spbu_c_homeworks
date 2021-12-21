#include "heap.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void getPath(int* p, int i, int start, int* path, int* k)
{
    if (i == start) {
        *k = 0;
        path[0] = start;
        return;
    }
    getPath(p, p[i], start, path, k);
    (*k)++;
    path[*k] = i;
}

int dijkstra(int** graph, int nVertexes, int start, int finish, int* path, int* pathLength)
{
    int* value = calloc(nVertexes, sizeof(int));
    int* previous = calloc(nVertexes, sizeof(int));
    Heap* heap = createHeap(nVertexes * nVertexes);
    for (int i = 0; i < nVertexes; i++) {
        value[i] = INT_MAX;
        insert(heap, (Pair) { INT_MAX, i });
        previous[i] = -1;
    }
    value[start] = 0;
    insert(heap, (Pair) { 0, start });

    while (heap->size > 0) {
        Pair pair = extractMin(heap);
        while (pair.first != value[pair.second])
            pair = extractMin(heap);
        if (pair.second == INT_MAX)
            break;
        int v = pair.second;
        for (int j = 0; j < nVertexes; j++) {
            if (graph[v][j] != -1 && value[v] + graph[v][j] < value[j]) {
                value[j] = value[v] + graph[v][j];
                insert(heap, (Pair) { value[v] + graph[v][j], j });
                previous[j] = v;
            }
        }
    }
    getPath(previous, finish, start, path, pathLength);
    int result = value[finish];
    deleteHeap(heap);
    free(value);
    free(previous);
    return result;
}

int main()
{
    int nVertexes = 0, start = 0, nEdges = 0, finish = 0;
    scanf("%d %d", &nVertexes, &nEdges);
    int** graph = malloc(nVertexes * sizeof(int*));
    for (int i = 0; i < nVertexes; i++)
        graph[i] = calloc(nVertexes, sizeof(int));
    for (int i = 0; i < nVertexes; i++)
        for (int j = 0; j < nVertexes; j++)
            graph[i][j] = -1;
    for (int i = 0; i < nEdges; i++) {
        int from = 0, to = 0, length = 0;
        scanf("%d %d %d", &from, &to, &length);
        graph[from][to] = length;
    }
    scanf("%d %d", &start, &finish);
    int* path = calloc(nVertexes, sizeof(int));
    int pathLength = 0;
    int pathValue = dijkstra(graph, nVertexes, start, finish, path, &pathLength);
    if (pathValue == INT_MAX)
        printf("start and finish are not connected");
    else {
        printf("%d %d\n", pathLength, pathValue);
        for (int i = 0; i < pathLength + 1; i++)
            printf("%d ", path[i]);
    }
    for (int i = 0; i < nVertexes; i++)
        free(graph[i]);
    free(graph);
    free(path);
    return 0;
}