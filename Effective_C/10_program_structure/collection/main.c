#include "collection.h"
#include <stdio.h>

int main() {
    Collection* c = collection_create();
    for (int i = 0; i < 5; i++) {
        collection_add(c, i * 10);
    }

    for (int i = 0; i < 5; i++) {
        printf("c[%d] = %d\n", i, collection_get(c, i));
    }

    collection_destroy(c);
    return 0;
}
