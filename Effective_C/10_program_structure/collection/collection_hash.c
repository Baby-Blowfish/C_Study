#include "collection.h"
#include <stdlib.h>

#define TABLE_SIZE 64

struct Collection {
    int* table;
    int  count;
};

Collection* collection_create(void) {
    Collection* c = malloc(sizeof(Collection));
    c->table = calloc(TABLE_SIZE, sizeof(int));
    c->count = 0;
    return c;
}

void collection_add(Collection* c, int value) {
    int i = value % TABLE_SIZE;
    while (c->table[i] != 0) {
        i = (i + 1) % TABLE_SIZE;
    }
    c->table[i] = value;
    c->count++;
}

int collection_get(const Collection* c, int index) {
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (c->table[i] != 0) {
            if (found == index) return c->table[i];
            found++;
        }
    }
    return -1;
}

void collection_destroy(Collection* c) {
    free(c->table);
    free(c);
}
