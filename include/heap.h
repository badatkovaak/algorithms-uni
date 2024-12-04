#ifdef HEAP_H
#define HEAP_H

typedef struct {
    void **data;
    unsigned long len;
} heap_array;

heap_array construct_binary_heap(heap_array array,
                                 int (*comparator)(void *, void *)) {}

void normalize(heap_array heap, unsigned index,
               int (*comparator)(void *, void *)) {}

#endif // HEAP_H
