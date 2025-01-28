#include "linked_list.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define P 1000000007
#define X 263

typedef struct {
    bool is_multiple;
    union {
        LinkedList *list;
        char *str;
    } value;
} TableItem;

uint64_t h(char *str, uint64_t len) {
    uint64_t res = 0;

    for (uint64_t i = 0; i < len; i++) {
        uint64_t x = 1;

        for (uint64_t j = 1; j < i; j++)
            x = (x * 263) % P;

        res = (res + x * str[i]) % P;
    }

    return res;
}

TableItem *create_table(uint64_t m) {
    TableItem *table = malloc(sizeof(TableItem) * m);
    memset(table, 0, m);
    return table;
}

void add_table_item(TableItem *table, char *str, uint64_t len) {
    uint64_t index = h(str, len);

    if (table[index].is_multiple)
        list_push(&(table[index].value.list), str);
    else {
        if (table[index].value.str) {
            LinkedList *new_multiple_entry = malloc(sizeof(LinkedList));
            *new_multiple_entry = (LinkedList){0, str};
            list_push(&new_multiple_entry, table[index].value.str);
            table[index].is_multiple = true;
            table[index].value.list = new_multiple_entry;
        } else
            table[index].value.str = str;
    }
}

/*void handle_command(char* command) {*/
/**/
/*}*/

int main() {
    printf("%lu\n", h("hi", 2));
    return 0;
}
