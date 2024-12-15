#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_MALLOC(x) malloc(x)

#define LIST_FREE(x) free(x)

typedef struct {
    void *next;
    void *data;
} LinkedList;

void push(LinkedList **list, void *value) {
    if (!(*list)) {
        *list = malloc(sizeof(LinkedList));
        **list = (LinkedList){0, value};
        return;
    }

    LinkedList *list_item = *list;

    while (list_item->next) {
        list_item = list_item->next;
    }

    LinkedList *new_elem = LIST_MALLOC(sizeof(LinkedList));
    *new_elem = (LinkedList){0, value};
    list_item->next = new_elem;
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

void *pop_front(LinkedList **list_ref) {
    void *result = get(*list_ref, 0);
    LinkedList *head = (*list_ref)->next;
    LIST_FREE(*list_ref);
    *list_ref = head;

    return result;
}

int list_length(LinkedList *list) {
    int len = 1;

    while (list->next) {
        len++;
        list = list->next;
    }

    return len;
}

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
        *str = malloc(sizeof(String));
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

typedef struct {
    char data;
    unsigned code_len;
} htable_item;

htable_item *build_huffman_table(unsigned *codes, unsigned longest_code_len) {
    unsigned a = (1 << longest_code_len);

    unsigned long htable_size = a * sizeof(htable_item);
    htable_item *table = malloc(htable_size);
    memset(table, 0, htable_size);

    for (int i = 0; i < 26; i++) {
        unsigned code = codes[i];

        if (!code)
            continue;

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

    return table;
}

char *decode_str(htable_item *table, char *encoded, unsigned longest_code_len) {
    unsigned long encoded_len = strlen(encoded);
    char *decoded = malloc(encoded_len);
    memset(decoded, 0, encoded_len);

    unsigned item_code = 0;
    unsigned index = 0;

    int i = 0;
    while (i < encoded_len) {
        item_code = 0;

        for (int j = 0; j < longest_code_len; j++) {
            item_code = (item_code << 1) + (encoded[i + j] == '1');
        }

        htable_item item = table[item_code];
        decoded[index++] = item.data;
        i += item.code_len;
    }

    printf("%s\n", decoded);

    return decoded;
}

char *read_file(char *path) {
    FILE *f = fopen(path, "r");

    if (!f)
        return 0;

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    buffer[size] = '\0';

    fread(buffer, size, 1, f);
    return buffer;
}

LinkedList *split_at(char *str, unsigned long len, char separator) {
    LinkedList *pieces_list = 0;

    String *current_piece = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != separator) {
            push_char(&current_piece, str[i]);
            continue;
        }

        push(&pieces_list, current_piece);

        current_piece = 0;
    }

    if (current_piece) {
        push(&pieces_list, current_piece);
    }

    return pieces_list;
}

unsigned chars_to_code(char *str) {
    unsigned i = 0;
    unsigned result = 1;

    while (str[i]) {
        if (str[i] != '1' && str[i] != '0') {
            i++;
            continue;
        }

        result = (result << 1) + (str[i] == '1');
        i++;
    }

    return result;
}

unsigned *create_codes_table(LinkedList *code_strs) {
    unsigned *table = malloc(sizeof(unsigned) * 26);
    memset(table, 0, sizeof(unsigned) * 26);

    while (code_strs->next) {
        String *str = code_strs->data;
        LinkedList *s = split_at(str->data, str->len, ':');
        unsigned table_index = ((String *)s->data)->data[0];
        char *code_str = ((String *)((LinkedList *)s->next)->data)->data;
        table[table_index - 'a'] = chars_to_code(code_str);
        code_strs = code_strs->next;
    }

    return table;
}

int main() {
    char *input = read_file("input.txt");
    LinkedList *lines = split_at(input, strlen(input), '\n');

    LinkedList *lines_from_2 = lines->next;
    unsigned *codes_table = create_codes_table(lines_from_2);

    LinkedList *lines_last = lines_from_2;
    while (lines_last->next) {
        lines_last = lines_last->next;
    }

    char *encoded_string = ((String *)lines_last->data)->data;

    unsigned longest_code_len = 0;
    for (int i = 0; i < 26; i++) {
        if (!codes_table[i]) {
            continue;
        }

        unsigned code_len = 0;
        unsigned temp = 1;

        while (temp <= codes_table[i]) {
            temp = temp << 1;
            code_len++;
        }

        code_len -= 1;

        if (longest_code_len < code_len) {
            longest_code_len = code_len;
        }
    }

    htable_item *htable = build_huffman_table(codes_table, longest_code_len);
    char *result = decode_str(htable, encoded_string, longest_code_len);

    return 0;
}
