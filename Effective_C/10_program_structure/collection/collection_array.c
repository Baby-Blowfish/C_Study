#include "collection.h"
#include <stdlib.h>

struct Collection {
    int* data;
    int  size;
    int  capacity;
};

Collection* collection_create(void) {
    struct Collection* c = malloc(sizeof(struct Collection));
    c->data = malloc(sizeof(int) * 8);
    c->capacity = 8;
    c->size = 0;
    return c;
}

void collection_add(Collection* c, int value) {
    if (c->size == c->capacity) {
        c->capacity *= 2;
        c->data = realloc(c->data, sizeof(int) * c->capacity);
    }
    c->data[c->size++] = value;
}

int collection_get(const Collection* c, int index) {
    return (index >= 0 && index < c->size) ? c->data[index] : -1;
}

void collection_destroy(Collection* c) {
    free(c->data);
    free(c);
}
