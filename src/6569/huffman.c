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

unsigned partition(void **array, int lo, int hi, int (*func)(void *, void *)) {
    int pivot = hi;
    int i = lo;
    void *temp;

    printf("pivot is - %u lo - %u  hi - %u \n", pivot, lo, hi);
    printf("pivot is - %i\n", *(int *)array[pivot]);

    for (int j = lo; j <= hi; j++) {
        printf("before - %lu %i\n", array[j], *(int *)array[j]);
    }
    puts("");

    for (int j = lo; j < hi; j++) {
        if (func(array[j], array[pivot]) <= 0) {
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            i++;
        }
    }

    puts("");
    for (int j = lo; j <= hi; j++) {
        printf("after 1 - %lu %i\n", array[j], *(int *)array[j]);
    }
    puts("");

    temp = array[hi];
    array[hi] = array[i];
    array[i] = temp;

    printf("%u %i\n", i, *(int *)array[i]);
    for (unsigned j = lo; j <= hi; j++) {
        printf("after 2 - %lu %i\n", array[j], *(int *)array[j]);
    }
    puts("");

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

TreeGeneric *create_huffman_codes(char *str, unsigned long len) {
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
            printf("%c - %u\n", leaves[i]->data, array[leaves[i]->data - 'a']);
    }

    /*puts("here2");*/
    bubblesort((void **)leaves, 26, compare_tree_nodes);

    puts("here3");
    for (int i = 0; i <= 25; i++) {
        printf("%c\n", leaves[i]->data);
    }

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

    while (list_length(leaves_list) >= 2) {
        printf(" -------------- \n");
        LinkedList *current = leaves_list;

        while (current) {
            print_tree(current->data, 0);
            current = current->next;
        }

        printf("\n");

        TreeGeneric *node1 = pop_front(&leaves_list);
        TreeGeneric *node2 = pop_front(&leaves_list);

        /*print_tree(node1, 0);*/
        /*print_tree(node2, 0);*/

        TreeNode *new_node = malloc(sizeof(TreeNode));
        *new_node =
            (TreeNode){NT_Node, node1->count + node2->count, node1, node2};
        insert_keeping_sorted(&leaves_list, (void *)new_node);
    }

    print_tree(leaves_list->data, 0);

    return leaves_list->data;
}

int main() {
    /*TreeNode *a = malloc(sizeof(TreeNode));*/
    /*print_tree(a, 0);*/
    /**a = (TreeNode){NT_Node, 10, 0, 0};*/

    /*srand(time(0));*/
    /**/
    /*unsigned long LEN = 10;*/
    /*int **array = malloc(sizeof(int *) * LEN);*/
    /**/
    /*for (int i = 0; i < LEN; i++) {*/
    /*    array[i] = malloc(sizeof(int));*/
    /*    *array[i] = rand() % 100;*/
    /*    printf("%i \n", *array[i]);*/
    /*}*/
    /**/
    /*printf("\n");*/
    /*quicksort(array, 0, LEN - 1, compare);*/
    /**/
    /*printf("\n");*/
    /*for (int i = 0; i < LEN; i++) {*/
    /*    printf("%i\n", *array[i]);*/
    /*}*/

    char *str = "abacabadyyy";
    /*char *str = "somerandomstring";*/
    create_huffman_codes(str, strlen(str));
}
