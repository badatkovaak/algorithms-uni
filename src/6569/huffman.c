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

    for (unsigned i = 0; i < len; i++)
        array[str[i] - 'a']++;

    TreeLeaf **leaves = malloc(sizeof(TreeLeaf) * 26);
    for (unsigned i = 'a'; i <= 'z'; i++)
        leaves[i - 'a'] = create_tree_leaf(i, array[i - 'a']);

    quicksort((void **)leaves, 0, 25, compare_tree_nodes);

    LinkedList *leaves_list = malloc(sizeof(LinkedList));
    *leaves_list = (LinkedList){0, leaves[25]};

    for (unsigned i = 24; i >= 0; i--)
        push(leaves_list, leaves[i]);

    /*while (leaves_list->next) {*/
    /*}*/

    return 0;
}
int main() { return 0; }
