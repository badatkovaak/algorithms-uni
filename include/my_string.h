#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdlib.h>
#include <string.h>

#define STARTING_CAPACITY 16

typedef struct {
    char *data;
    unsigned len;
    unsigned capacity;
} String;

String *create_from_null_terminated(char *str) {
    unsigned len = strlen(str);
    unsigned capacity = 1;
    while (capacity <= len) {
        capacity = capacity << 1;
    }

    if (capacity < STARTING_CAPACITY) {
        capacity = STARTING_CAPACITY;
    }

    char *data = malloc(capacity);
    memset(data, 0, capacity);
    memmove(data, str, len);

    String *result = malloc(sizeof(String));
    *result = (String){data, len, capacity};
    return result;
}

void push_char(String **str, char c) {
    if (!(*str)) {
        (*str) = malloc(sizeof(String));
        (*str)->len = 1;
        (*str)->capacity = STARTING_CAPACITY;

        (*str)->data = malloc(STARTING_CAPACITY);
        memset((*str)->data, 0, STARTING_CAPACITY);
        (*str)->data[0] = c;
        return;
    }

    String *s = *str;

    if (s->capacity - s->len > 1) {
        s->data[s->len] = c;
        s->len++;
        return;
    }

    char *new_data = malloc(s->capacity * 2);
    memset(new_data, 0, s->capacity * 2);
    memmove(new_data, s->data, s->capacity * 2);
    s->data = new_data;
    s->data[s->len] = c;
    s->len++;
    s->capacity *= 2;
    return;
}

#endif // !MY_STRING_H
