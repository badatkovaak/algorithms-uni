#ifdef HEAP_H
#define HEAP_H

#include <stdint.h>

typedef struct {
    void **data;
    uint64_t len;
} heap_array;

heap_array construct_binary_heap(heap_array array,
                                 int (*comparator)(void *, void *)) {}

void normalize(heap_array heap, unsigned index,
               int (*comparator)(void *, void *)) {}

#endif // HEAP_H
