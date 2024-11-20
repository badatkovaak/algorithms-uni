#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST
#include "base.h"

typedef enum {
    Node,
    Leaf,
} NodeType;

typedef struct {
    NodeType type;
    char data;
    unsigned count;
} TreeLeaf;

typedef struct {
    NodeType type;
    unsigned count;
    void *left;
    void *right;
} TreeNode;

unsigned partition(void **array, unsigned lo, unsigned hi,
                   int (*func)(void *, void *)) {
    unsigned pivot = hi;
    unsigned i = lo;
    void *temp;

    for (unsigned j = lo; j < hi; j++) {
        if (func(array[pivot], array[i]) >= 0) {
            temp = array[pivot];
            array[pivot] = array[i];
            array[i] = temp;
            i++;
        }
    }

    temp = array[hi];
    array[hi] = array[i];
    array[i] = temp;

    return pivot;
}

void quicksort(void **array, unsigned lo, unsigned hi,
               int (*func)(void *, void *)) {
    if (lo >= hi)
        return;

    unsigned p = partition(array, lo, hi, func);

    quicksort(array, lo, p - 1, func);
    quicksort(array, p, hi, func);
}

int compare_tree_nodes(void *lhs, void *rhs) {
    return ((TreeLeaf *)lhs)->count - ((TreeLeaf *)rhs)->count;
}

TreeLeaf *create_tree_leaf(char data, unsigned count) {
    TreeLeaf *leaf = malloc(sizeof(TreeLeaf));
    *leaf = (TreeLeaf){Leaf, data, count};
    return leaf;
}

TreeNode *create_tree_node(unsigned count, void *left, void *right) {
    TreeNode *node = malloc(sizeof(TreeNode));
    *node = (TreeNode){Node, count, left, right};
    return node;
}

TreeLeaf *create_huffman_codes(char *str, unsigned long len) {
    unsigned *array = malloc(sizeof(unsigned) * 26);
    memset(array, 0, sizeof(unsigned) * 26);

    puts("This function doesn't need newline.");

    for (unsigned i = 0; i < len; i++)
        array[str[i] - 'a']++;

    for (int i = 0; i < 26; i++) {
        printf("array - %u\n", array[i]);
    }

    puts("here1");

    TreeLeaf **leaves = malloc(sizeof(TreeLeaf) * 26);
    for (unsigned i = 'a'; i <= 'z'; i++)
        leaves[i - 'a'] = create_tree_leaf(i, array[i - 'a']);

    for (int i = 0; i <= 25; i++) {
        if (array[leaves[i]->data - 'a'] > 0)
            printf("%c\n", leaves[i]->data);
    }

    puts("here2");
    quicksort((void **)leaves, 0, 25, compare_tree_nodes);

    puts("here3");
    for (int i = 0; i <= 25; i++) {
        printf("%c\n", leaves[i]->data);
    }

    LinkedList *leaves_list = malloc(sizeof(LinkedList));
    /**leaves_list = (LinkedList){0, leaves[25]};*/
    for (int i = 25; i >= 0; i--) {
        if (array[leaves[i]->data - 'a'] > 0) {
            *leaves_list = (LinkedList){0, leaves_list};
            break;
        }

        if (i == 0)
            __builtin_trap();
    }

    puts("here4");
    for (int i = 24; i >= 0; i--) {
        printf("%c\n", leaves[i]->data);
        if (array[i] > 0)
            push(leaves_list, leaves[i]);
    }

    puts("here5");
    LinkedList *current = leaves_list;
    while (current) {
        printf("%c \n", *(char *)current->data);
        current = current->next;
    }

    /*while (leaves_list->next) {*/
    /*}*/

    return 0;
}

int main() {
    char *str = "abacabad";
    create_huffman_codes(str, strlen(str));
}
