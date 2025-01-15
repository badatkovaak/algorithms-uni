#include "linked_list.h"
#include <stdio.h>
#include <string.h>

#define P 1000000007
#define X 263

typedef union {
    unsigned long tag;
    LinkedList item;
} TableItem;

unsigned h(char *str, unsigned len) {
    unsigned res = 0;

    for (unsigned i = 0; i < len; i++) {
        unsigned x = 1;

        for (int j = 1; j < i; j++)
            /*for (int j = len; j > i; j--)*/
            x = (x * 263) % P;

        res = (res + x * str[i]) % P;
    }

    return res;
}

TableItem *create_table(unsigned m) {
    TableItem *table = malloc(sizeof(TableItem) * m);
    memset(table, 0, m);
    return table;
}

void add_table_item(char *str, unsigned len) {
    unsigned index = h(str, len);
    /*if()*/
}

int main() {
    printf("%u\n", h("hi", 2));
    return 0;
}
