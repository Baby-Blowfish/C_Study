#include "collection.h"
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

struct Collection {
    Node* head;
};

Collection* collection_create(void) {
    Collection* c = malloc(sizeof(Collection));
    c->head = NULL;
    return c;
}

void collection_add(Collection* c, int value) {
    Node* n = malloc(sizeof(Node));
    n->value = value;
    n->next = c->head;
    c->head = n;
}

int collection_get(const Collection* c, int index) {
    Node* current = c->head;
    for (int i = 0; i < index && current; i++) {
        current = current->next;
    }
    return current ? current->value : -1;
}

void collection_destroy(Collection* c) {
    Node* curr = c->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    free(c);
}
