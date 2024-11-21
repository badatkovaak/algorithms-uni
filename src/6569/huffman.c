#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST
#include "base.h"

typedef enum {
    NT_Node,
    NT_Leaf,
} NodeType;

typedef struct {
    NodeType type;
    unsigned count;
} TreeGeneric;

typedef struct {
    NodeType type;
    unsigned count;
    char data;
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

void print_tree(TreeGeneric *tree, unsigned depth) {
    for (unsigned i = 0; i < depth; i++) {
        printf("\t");
    }

    if (!tree) {
        printf("Null\n");
        return;
    }

    switch (tree->type) {
    case NT_Leaf: {
        TreeLeaf *leaf = tree;
        printf("Leaf - %i %c\n", leaf->count, leaf->data);
    }
    case NT_Node: {
        TreeNode *node = tree;
        printf("Node - %i %lu %lu\n", node->count, node->left, node->right);
        print_tree(node->left, depth + 1);
        print_tree(node->right, depth + 1);
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

TreeLeaf *create_huffman_codes(char *str, unsigned long len) {
    unsigned *array = malloc(sizeof(unsigned) * 26);
    memset(array, 0, sizeof(unsigned) * 26);

    for (unsigned i = 0; i < len; i++)
        array[str[i] - 'a']++;

    /*for (int i = 0; i < 26; i++) {*/
    /*    printf("array - %u\n", array[i]);*/
    /*}*/

    /*puts("here1");*/

    TreeLeaf **leaves = malloc(sizeof(TreeLeaf) * 26);
    for (unsigned i = 'a'; i <= 'z'; i++)
        leaves[i - 'a'] = create_tree_leaf(i, array[i - 'a']);

    for (int i = 0; i <= 25; i++) {
        if (array[leaves[i]->data - 'a'] > 0)
            printf("%c\n", leaves[i]->data);
    }

    /*puts("here2");*/
    quicksort((void **)leaves, 0, 25, compare_tree_nodes);

    /*puts("here3");*/
    /*for (int i = 0; i <= 25; i++) {*/
    /*    printf("%c\n", leaves[i]->data);*/
    /*}*/

    LinkedList *leaves_list = malloc(sizeof(LinkedList));
    for (int i = 25; i >= 0; i--) {
        if (array[leaves[i]->data - 'a'] > 0) {
            *leaves_list = (LinkedList){0, leaves[i]};
            break;
        }
    }

    puts("here4");
    for (int i = 24; i >= 0; i--) {
        if (array[leaves[i]->data - 'a'] > 0) {
            printf("%c\n", leaves[i]->data);
            push(leaves_list, leaves[i]);
        }
    }

    /*puts("here5");*/

    LinkedList *current = leaves_list;
    while (current) {
        printf("leaves_list - %c \n", ((TreeLeaf *)current->data)->data);
        current = current->next;
    }

    printf("first - %c \n", ((TreeLeaf *)leaves_list->data)->data);

    LinkedList *stack_top = leaves_list;
    LinkedList *stack_next = leaves_list->next;
    LinkedList *stack_next_next = stack_next->next;

    while (list_length(stack_top) >= 2) {
        printf("stack - %lu %lu %lu\n", stack_top, stack_next, stack_next_next);

        TreeNode *new_node = malloc(sizeof(TreeNode));
        TreeGeneric *left = stack_top->data;
        TreeGeneric *right = stack_next->data;
        print_tree(left, 0);
        print_tree(right, 0);

        *new_node = (TreeNode){
            NT_Node,
            left->count + right->count,
            left,
            right,
        };

        /*LinkedList *new_item = malloc(sizeof(LinkedList));*/
        *stack_top = (LinkedList){stack_next->next, new_node};
        stack_next = stack_next_next;
        /**stack_next_next = stack_next_next->next);*/
        if (stack_next) {
            stack_next_next = stack_next->next;
        } else {
            stack_next_next = 0;
        }
    }

    puts("done");

    print_tree(stack_top->data, 0);

    return 0;
}

int main() {
    char *str = "abacabad";
    create_huffman_codes(str, strlen(str));
}
