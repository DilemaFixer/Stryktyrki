#ifndef L_LIST
#define L_LIST

#include <stdlib.h>

typedef struct node_t {
    struct node_t* next;
} node_t;

typedef struct l_list {
    node_t* head;
    size_t count;
    void (*free_custom_node)(node_t *node);
} l_list;

l_list *new_empty_linked_list();
l_list *new_linked_list_with_node(node_t *node);
void free_linked_list(l_list *l_list);
void free_node(node_t *node , void (*free_custom_node)(node_t *node));
void free_node_not_recursively(node_t *node , void (*free_custom_node)(node_t *node));

void linked_list_add_at(l_list *list , node_t *node , size_t index);
void linked_list_add(l_list *list , node_t *node);
void linked_list_add_last(l_list *list , node_t *node);

void linked_list_remove_at(l_list *list , size_t index);
void linked_list_remove_first(l_list *list);
void linked_list_remove_last(l_list *list);

void* find_at_linked_list(l_list *list, void* (*selector)(size_t *i, node_t *node, void *context), void *context);
void* find_all_at_linked_list(l_list *list, void* (*selector)(size_t *i, node_t *node, void *context), void *context);
#endif
