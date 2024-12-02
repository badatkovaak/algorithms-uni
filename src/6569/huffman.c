#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST_MALLOC(x) malloc(x)
#define LIST_FREE(x) free(x)

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

#define NT_Node 1ul
#define NT_Leaf 2ul

typedef struct {
    unsigned long type;
    unsigned long count;
} TreeGeneric;

typedef struct {
    unsigned long type;
    unsigned long count;
    char data;
} TreeLeaf;

typedef struct {
    unsigned long type;
    unsigned long count;
    void *left;
    void *right;
} TreeNode;

unsigned partition(void **array, int lo, int hi, int (*func)(void *, void *)) {
    int pivot = hi;
    int i = lo;
    void *temp;

    for (int j = lo; j < hi; j++) {
        if (func(array[j], array[pivot]) <= 0) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
        }
    }

    temp = array[hi];
    array[hi] = array[i];
    array[i] = temp;

    return i;
}

void quicksort(void **array, int lo, int hi, int (*func)(void *, void *)) {
    if (lo >= hi || lo < 0)
        return;

    unsigned p = partition(array, lo, hi, func);

    quicksort(array, lo, p - 1, func);
    quicksort(array, p, hi, func);
}

void bubblesort(void **array, unsigned long len, int (*func)(void *, void *)) {
    for (unsigned i = 0; i < len - 1; i++) {
        for (unsigned j = 0; j < len - i - 1; j++) {
            if (func(array[j], array[j + 1]) > 0) {
                void *temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

int compare_tree_nodes(void *lhs, void *rhs) {
    return ((TreeGeneric *)lhs)->count - ((TreeGeneric *)rhs)->count;
}

void print_tree(TreeGeneric *tree, unsigned depth) {
    for (unsigned i = 0; i < depth; i++) {
        printf("\t");
    }

    if (tree == 0) {
        printf("Null\n");
        return;
    }

    switch (tree->type) {
        case NT_Leaf: {
            TreeLeaf *leaf = (TreeLeaf *)tree;
            printf("Leaf - %lu %c\n", leaf->count, leaf->data);
            break;
        }
        case NT_Node: {
            TreeNode *node = (TreeNode *)tree;
            printf("Node - %lu\n", node->count);
            print_tree(node->left, depth + 1);
            print_tree(node->right, depth + 1);
            break;
        }
    }
    return;
}

TreeLeaf *create_tree_leaf(char data, unsigned count) {
    TreeLeaf *leaf = malloc(sizeof(TreeLeaf));
    *leaf = (TreeLeaf){NT_Leaf, count, data};
    return leaf;
}

TreeNode *create_tree_node(unsigned count, void *left, void *right) {
    TreeNode *node = malloc(sizeof(TreeNode));
    *node = (TreeNode){NT_Node, count, left, right};
    return node;
}

void insert_keeping_sorted(LinkedList **list, TreeGeneric *node) {
    LinkedList *head = *list;

    if (!(*list)) {
        LinkedList *new_item = malloc(sizeof(LinkedList));
        *new_item = (LinkedList){0, node};
        *list = new_item;
        return;
    }

    LinkedList *current = head->next;
    LinkedList *previous = head;

    if (((TreeGeneric *)previous->data)->count >= node->count) {
        LinkedList *new_item = malloc(sizeof(LinkedList));
        *new_item = (LinkedList){head, node};
        *list = new_item;
        return;
    }

    if (!current) {
        LinkedList *new_item = malloc(sizeof(LinkedList));
        *new_item = (LinkedList){0, node};
        head->next = new_item;
        return;
    }

    while (((TreeGeneric *)current->data)->count < node->count) {
        previous = current;
        current = current->next;

        if (!current) {
            break;
        }
    }

    LinkedList *new_item = malloc(sizeof(LinkedList));
    *new_item = (LinkedList){current, node};
    previous->next = new_item;
}

TreeGeneric *create_huffman_tree(char *str, unsigned long len) {
    unsigned *array = malloc(sizeof(unsigned) * 26);
    memset(array, 0, sizeof(unsigned) * 26);
    for (unsigned i = 0; i < len; i++)
        array[str[i] - 'a']++;

    TreeLeaf **leaves = malloc(sizeof(TreeLeaf) * 26);
    for (unsigned i = 0; i < 26; i++)
        leaves[i] = create_tree_leaf(i + 'a', array[i]);

    quicksort((void **)leaves, 0, 25, compare_tree_nodes);

    LinkedList *leaves_list = malloc(sizeof(LinkedList));
    int j = 0;
    for (int i = 0; i < 26; i++) {
        if (array[leaves[i]->data - 'a'] > 0) {
            *leaves_list = (LinkedList){0, leaves[i]};
            j = i;
            break;
        }
    }

    for (int i = j + 1; i < 26; i++) {
        if (array[leaves[i]->data - 'a'] > 0)
            push(leaves_list, leaves[i]);
    }

    while (list_length(leaves_list) >= 2) {
        TreeGeneric *node1 = pop_front(&leaves_list);
        TreeGeneric *node2 = pop_front(&leaves_list);

        TreeNode *new_node = malloc(sizeof(TreeNode));
        *new_node =
            (TreeNode){NT_Node, node1->count + node2->count, node1, node2};
        insert_keeping_sorted(&leaves_list, (void *)new_node);
    }

    return leaves_list->data;
}

char *code_to_str(int code) {
    unsigned len = 1;
    int temp = code;

    while (temp > 1) {
        temp = temp >> 1;
        len++;
    }

    char *result = malloc(len);
    temp = code;
    result[len - 1] = '\0';
    int i = 0;

    while (temp > 1) {
        if (temp % 2 == 1)
            result[len - i - 2] = '1';
        else
            result[len - i - 2] = '0';

        temp = temp >> 1;
        i++;
    }

    return result;
}

void walk_huffman_tree(TreeGeneric *tree, char **table, int path) {
    switch (tree->type) {
        case NT_Node: {
            TreeNode *node = (TreeNode *)tree;
            walk_huffman_tree(node->left, table, (path << 1));
            walk_huffman_tree(node->right, table, (path << 1) + 1);
            break;
        }
        case NT_Leaf: {
            TreeLeaf *leaf = (TreeLeaf *)tree;
            table[leaf->data - 'a'] = code_to_str(path);
            break;
        }
    }
}

char **construct_huffman_table(TreeGeneric *huffman_tree) {
    char **result = malloc(sizeof(char *) * 26);
    memset(result, 0, sizeof(char *) * 26);

    if (huffman_tree->type == NT_Node)
        walk_huffman_tree(huffman_tree, result, 1);
    else {
        TreeLeaf *leaf = (TreeLeaf *)huffman_tree;
        result[leaf->data - 'a'] = "0";
    }

    return result;
}

void huffman_encode_str(char *str, unsigned long len, char **table) {
    unsigned longest_length = 0;
    unsigned unique_count = 0;

    for (int i = 0; i < 26; i++) {
        if (table[i] != 0 && table[i][0] != 0) {
            unsigned long curr_len = strlen(table[i]);

            if (curr_len > longest_length)
                longest_length = curr_len;

            unique_count++;
        }
    }

    char *result = malloc(len * longest_length + 1);
    result[len * longest_length] = '\0';
    unsigned long total_length = 0;

    for (int i = 0; i < len; i++) {
        char *curr_code = table[str[i] - 'a'];
        unsigned long curr_len = strlen(curr_code);

        for (int j = 0; j < curr_len; j++) {
            result[total_length++] = curr_code[j];
        }
    }

    printf("%u %lu\n", unique_count, total_length);

    for (int i = 0; i < 26; i++) {
        if (table[i] != 0 && table[i][0] != 0)
            printf("%c: %s\n", i + 'a', table[i]);
    }

    puts(result);
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

char *sanitize_input(char *str) {
    int i = 0;

    while (str[i]) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            i++;
            continue;
        }

        int j = i + 1;

        while (str[j]) {
            str[j - 1] = str[j];
            j++;
        }
        str[j - 1] = '\0';

        i++;
    }

    return str;
}

int main() {
    char *str = sanitize_input(read_file("input.txt"));
    size_t len = strlen(str);

    TreeGeneric *tree = create_huffman_tree(str, len);
    char **table = construct_huffman_table(tree);
    huffman_encode_str(str, len, table);
}
