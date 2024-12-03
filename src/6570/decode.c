#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char data;
    unsigned code_len;
} htable_item;

htable_item *build_huffman_table(unsigned *codes, unsigned longest_code_len) {
    assert(longest_code_len < 26);

    unsigned a = (1 << longest_code_len);
    printf("longest is %u ; %b\n", longest_code_len, a);

    unsigned long htable_size = a * sizeof(htable_item);
    htable_item *table = malloc(htable_size);
    memset(table, 0, htable_size);

    for (int i = 0; i < 26; i++) {
        unsigned code = codes[i];

        if (!code)
            continue;

        printf("code is %b\n", code);

        int count = 0;
        unsigned lower_bound = code;
        while (a > lower_bound) {
            lower_bound = lower_bound << 1;
            count++;
        }

        unsigned upper_bound = code;
        while (a > upper_bound)
            upper_bound = (upper_bound << 1) + 1;

        upper_bound = upper_bound ^ a;
        lower_bound = lower_bound ^ a;

        for (int j = lower_bound; j <= upper_bound; j++) {
            table[j] = (htable_item){i + 'a', longest_code_len - count};
        }
    }

    for (unsigned i = 0; i < a; i++) {
        printf("%b %c %u\n", i, table[i].data, table[i].code_len);
    }

    return table;
}

int main() {
    unsigned *codes = malloc(26 * sizeof(unsigned));
    memset(codes, 0, 26 * sizeof(unsigned));
    /*codes[0] = 0b11;*/
    /*codes[1] = 0b101;*/
    /*codes[2] = 0b1000;*/
    /*codes[3] = 0b1001;*/
    codes[0] = 0b10;
    codes[1] = 0b110;
    codes[2] = 0b1111;
    codes[3] = 0b1110;

    build_huffman_table(codes, 3);

    return 0;
}
