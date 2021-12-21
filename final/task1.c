#include "../library/TreeMap/TreeMap.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number = 0, newCount = 0;
    TreeMap* map = createTreeMap(compare);
    scanf("%d", &number);
    while (number) {
        Value count = get(map, wrapInt(number));
        if (!isNone(count))
            newCount = getInt(get(map, wrapInt(number))) + 1;
        else
            newCount = 1;
        put(map, wrapInt(number), wrapInt(newCount));
        scanf("%d", &number);
    }
    TreeMapIterator* iterator = getIterator(map);
    while (hasElement(iterator)) {
        printf("%d %d\n", getInt(getIteratorKey(iterator)), getInt(getIteratorValue(iterator)));
        next(iterator);
    }
    freeTreeMapIterator(iterator);
    deleteTreeMap(map);
}