#ifndef BASE_H
#define BASE_H

#ifdef LIST

#ifndef LIST_MALLOC
#define LIST_MALLOC(x) malloc(x)
#include <stdlib.h>
#endif // !LIST_MALLOC

#ifndef LIST_FREE
#define LIST_FREE(x) free(x)
#include <stdlib.h>
#endif // !LIST_FREE

typedef struct {
    void *next;
    void *data;
} LinkedList;

void push(LinkedList *list, void *value) {
    while (list->next) {
        list = list->next;
    }

    LinkedList *new_elem = LIST_MALLOC(sizeof(LinkedList));
    *new_elem = (LinkedList){0, value};
    list->next = new_elem;
}

void *get(LinkedList *list, unsigned index) {
    unsigned i = 0;

    while (i < index) {
        if (list->next)
            list = list->next;
        else
            return 0;
    }

    return list->data;
}

void *pop(LinkedList *list) {
    LinkedList *current = list;
    LinkedList *next = list->next;

    while (next) {
        current = next;
        next = next->next;
    }

    void *res = next->data;
    current->next = 0;
    LIST_FREE(next);

    return res;
}

#endif // !LIST

#endif // !BASE_H
