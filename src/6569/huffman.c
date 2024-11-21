#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIST
#include "base.h"

/*typedef enum {*/
/*    NT_Node,*/
/*    NT_Leaf,*/
/*} NodeType;*/

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

    /*for (int i = 0; i <= 25; i++) {*/
    /*    if (array[leaves[i]->data - 'a'] > 0)*/
    /*        printf("%c\n", leaves[i]->data);*/
    /*}*/

    /*puts("here2");*/
    quicksort((void **)leaves, 0, 25, compare_tree_nodes);

    /*puts("here3");*/
    /*for (int i = 0; i <= 25; i++) {*/
    /*    printf("%c\n", leaves[i]->data);*/
    /*}*/

    int j = 0;

    LinkedList *leaves_list = malloc(sizeof(LinkedList));
    for (int i = 0; i < 26; i++) {
        if (array[leaves[i]->data - 'a'] > 0) {
            *leaves_list = (LinkedList){0, leaves[i]};
            j = i;
            break;
        }
    }

    for (int i = j + 1; i < 26; i++) {
        if (array[leaves[i]->data - 'a'] > 0) {
            printf("pushed %c\n", leaves[i]->data);
            push(leaves_list, leaves[i]);
        }
    }

    /*puts("here5");*/

    LinkedList *current = leaves_list;
    while (current) {
        printf("leaves_list - %c \n", ((TreeLeaf *)current->data)->data);
        current = current->next;
    }

    /*printf("first - %c \n", ((TreeLeaf *)leaves_list->data)->data);*/

    LinkedList *stack_top = leaves_list;
    LinkedList *stack_next = leaves_list->next;
    LinkedList *stack_next_next = stack_next->next;

    while (list_length(stack_top) >= 2) {
        /*printf("stack - %xl %xl %xl %i\n", stack_top, stack_next,*/
        /*stack_next_next, list_length(stack_top));*/

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

        LinkedList *start = stack_next_next;

        if (!stack_next_next) {
            *stack_top = (LinkedList){stack_next->next, new_node};
            break;
        }

        int set = 0;
        LinkedList *current = stack_next_next;
        LinkedList *previous = 0;

        while (current) {
            TreeGeneric *t = current->data;

            if (t->count >= new_node->count) {
                LinkedList *new_item = malloc(sizeof(LinkedList));

                if (previous) {
                    previous->next = new_item;
                    new_item->next = current;
                    new_item->data = new_node;
                } else {
                    new_item->next = current;
                    new_item->data = new_node;
                }

                set = 1;
                break;
            }

            previous = current;
            current = current->next;
        }

        /**stack_top = (LinkedList){stack_next->next, new_node};*/
        /*stack_next = stack_next_next;*/
        /**/
        /*if (stack_next) {*/
        /*    stack_next_next = stack_next->next;*/
        /*} else {*/
        /*    stack_next_next = 0;*/
        /*}*/
    }

    print_tree(stack_top->data, 0);

    return 0;
}

int main() {
    /*TreeNode *a = malloc(sizeof(TreeNode));*/
    /*print_tree(a, 0);*/
    /**a = (TreeNode){NT_Node, 10, 0, 0};*/

    char *str = "abacabadyyy";
    create_huffman_codes(str, strlen(str));
}
