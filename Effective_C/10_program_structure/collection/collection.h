#ifndef COLLECTION_H
#define COLLECTION_H

typedef struct Collection Collection;

Collection* collection_create(void);
void        collection_add(Collection*, int value);
int         collection_get(const Collection*, int index);
void        collection_destroy(Collection*);

#endif
