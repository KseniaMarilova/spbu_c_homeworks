#include "../library/Value/Value.h"
#include "../library/TreeMap/TreeMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void addSize(TreeMap* stock, int size, int count)
{
    Value found = get(stock->root, wrapInt(size));
    int actualCount = 0;
    if (!isNone(found))
        actualCount = getInt(found);
    put(stock, wrapInt(size), wrapInt(actualCount + count));
}

int getCount(TreeMap* stock, int size)
{
    Value result = get(stock->root, wrapInt(size));
    return isNone(result) ? 0 : getInt(result);
}

int selectSize(TreeMap* stock, int size)
{
    Value foundSize = getLowerBound(stock, wrapInt(size));
    if (isNone(foundSize))
        return -1;
    int count = getInt(get(stock->root, foundSize));
    if (count == 1)
        removeKey(stock, foundSize);
    else
        put(stock, foundSize, wrapInt(count - 1));
    return getInt(foundSize);
}

void printTreeMap(FILE* output, TreeMap* map)
{
    TreeMapIterator* iterator = getIterator(map);
    while (hasElement(iterator)) {
        fprintf(output, "%d %d\n", getInt(getKey(iterator)), getInt(getValue(iterator)));
        next(iterator);
    }
    freeTreeMapIterator(iterator);
}

bool checkInput(FILE* file1, FILE* file2, FILE* file3, FILE* file4)
{
    if (!file1) {
        printf("incorrect path to the shop balance file");
        return false;
    }
    if (!file2) {
        printf("incorrect path to the logList file");
        return false;
    }
    if (!file3) {
        printf("incorrect path to the output file");
        return false;
    }
    if (!file4) {
        printf("incorrect path to the output file");
        return false;
    }
    return true;
}

void readTreeMap(FILE* input, TreeMap* map)
{
    int size = 0, count = 0;
    while (fscanf(input, "%d %d", &size, &count) != EOF)
        put(map, wrapInt(size), wrapInt(count));
}

void readLog(FILE* logList, FILE* results, TreeMap* stock)
{
    char command[10] = "";
    fscanf(logList, "%s", command);
    if (!strcmp("ADD", command)) {
        int size = 0, count = 0;
        fscanf(logList, "%d %d", &size, &count);
        addSize(stock, size, count);
    } else if (!strcmp("GET", command)) {
        int size = 0;
        fscanf(logList, "%d", &size);
        fprintf(results, "%d\n", size);
    } else if (!strcmp("SELECT", command)) {
        int size = 0;
        fscanf(logList, "%d", &size);
        int foundSize = selectSize(stock, size);
        if (foundSize == -1)
            fprintf(results, "Sorry\n");
        else
            fprintf(results, "%d\n", foundSize);
    }
}

int main(int argc, char* argv[])
{
    if (argc != 5) {
        printf("wrong number of program arguments");
        return false;
    }
    FILE* startBalance = fopen(argv[1], "r");
    FILE* logList = fopen(argv[2], "r");
    FILE* results = fopen(argv[3], "w");
    FILE* finalBalance = fopen(argv[4], "w");
    if (!checkInput(startBalance, logList, results, finalBalance))
        return 0;
    TreeMap* stock = createTreeMap(INT_TYPE, INT_TYPE);
    readTreeMap(startBalance, stock);
    fclose(startBalance);
    int n = 0;
    fscanf(logList, "%d", &n);
    for (int i = 0; i < n; i++)
        readLog(logList, results, stock);
    fclose(logList);
    fclose(results);
    printTreeMap(finalBalance, stock);
    deleteTreeMap(stock);
    return 0;
}