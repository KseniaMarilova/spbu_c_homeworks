#include "value.h"
#include "avltree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void addSize(TreeMap* stock, int size, int count)
{
    int actualCount = getInt(get(stock, wrapInt(size)));
    put(stock, wrapInt(size), wrapInt(actualCount + count));
}

int getCount(TreeMap* stock, int size)
{
    Value result = get(stock, wrapInt(size));
    return isNone(result) ? 0 : getInt(result);
}

int selectSize(TreeMap* stock, int size)
{
    Value foundSize = getLowerBound(stock, wrapInt(size));
    if (isNone(foundSize))
        return -1;
    int count = getInt(get(stock, foundSize));
    if (count == 1)
        removeKey(stock, foundSize);
    else
        put(stock, foundSize, wrapInt(count - 1));
    return getInt(foundSize);
}

int main(int argc, char* argv[])
{
    FILE* balance = fopen(argv[1], "r");
    FILE* logList = fopen(argv[2], "r");
    if (argc != 3) {
        printf("wrong number of program arguments");
        return 0;
    }
    if (!balance) {
        printf("incorrect path to the balance file");
        return 0;
    }
    if (!logList) {
        printf("incorrect path to the logList file");
        return 0;
    }
    TreeMap* stock = createTreeMap(INT_TYPE, INT_TYPE);
    int size, count;
    while (fscanf(balance, "%d %d", &size, &count) != EOF)
        put(stock, wrapInt(size), wrapInt(count));
    fclose(balance);
    int n = 0;
    char command[10];
    fscanf(logList, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(logList, "%s", command);
        if (!strcmp("ADD", command)) {
            fscanf(logList, "%d %d", &size, &count);
            addSize(stock, size, count);
        } else if (!strcmp("GET", command)) {
            fscanf(logList, "%d", &size);
            printf("%d\n", getCount(stock, size));
        } else if (!strcmp("SELECTED", command)) {
            fscanf(logList, "%d", &size);
            int foundSize = selectSize(stock, size);
            if (foundSize == -1)
                printf("Sorry");
            else
                printf("%d\n", foundSize);
        }
    }
    fclose(logList);
    deleteTreeMap(stock);
}