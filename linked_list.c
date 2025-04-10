#include "linked_list.h"
#include "arr.h"

l_list *new_empty_linked_list() {
  l_list *list = (l_list *)malloc(sizeof(l_list));
  if (!list)
    lfatal("Error allocation memory for linked list struct");
  list->head = NULL;
  list->free_custom_node = NULL;
  list->count = 0;
  return list;
}

l_list *new_linked_list_with_node(node_t *node) {
  l_list *list = new_empty_linked_list();
  list->head = node;
  list->count = 1;
  return list;
}

void free_linked_list(l_list *list) {
  if (!list)
    return;
  free_node(list->head, list->free_custom_node);
  free(list);
}

void free_node(node_t *head, void (*free_custom_node)(node_t *node)) {
  node_t *current = head;
  node_t *next;
  while (current) {
    next = current->next;
    if (free_custom_node == NULL)
      free(current);
    else
      free_custom_node(current);
    current = next;
  }
}

void free_node_not_recursively(node_t *node,
                               void (*free_custom_node)(node_t *node)) {
  if (!node)
    return;
  if (free_custom_node == NULL)
    free(node);
  else
    free_custom_node(node);
}

void linked_list_remove_at(l_list *list, size_t index) {
  if (!list)
    return;
  if (!list->head)
    lfatal("Can't remove item at index %zu, list is empty", index);

  if (index == 0) {
    node_t *old = list->head;
    list->head = list->head->next;
    free_node_not_recursively(old, list->free_custom_node);
    list->count--;
    return;
  }

  node_t *current = list->head;
  size_t current_i = 0;

  while (current->next && current_i < index - 1) {
    current = current->next;
    current_i++;
  }

  if (!current->next)
    lfatal("Can't remove item at index %zu, index out of range", index);

  node_t *node_to_remove = current->next;
  current->next = node_to_remove->next;
  free_node_not_recursively(node_to_remove, list->free_custom_node);
  list->count--;
}

void linked_list_remove_first(l_list *list) {
  if (!list)
    return;
  linked_list_remove_at(list, 0);
}

void linked_list_remove_last(l_list *list) {
  if (!list)
    return;
  linked_list_remove_at(list, list->count - 1);
}

void linked_list_add_at(l_list *list, node_t *node, size_t index) {
  if (!list)
    lfatal("Can't add new node to linked list, list ptr is null");
  if (!node)
    lfatal("Can't add new node to linked list, node is null");

  if (index == 0 || !list->head) {
    node->next = list->head;
    list->head = node;
    list->count++;
    return;
  }

  if (index > list->count)
    lfatal("Can't add new node to linked list at index %zu, index out of range",
           index);

  node_t *current = list->head;
  size_t i = 0;

  while (current && i < index - 1) {
    current = current->next;
    i++;
  }

  if (!current)
    lfatal("Can't add item at index %zu, index out of range", index);

  node->next = current->next;
  current->next = node;
  list->count++;
}

void linked_list_add_first(l_list *list, node_t *node) {
  linked_list_add_at(list, node, 0);
}

void linked_list_add_last(l_list *list, node_t *node) {
  linked_list_add_at(list, node, list->count);
}

void *find_at_linked_list(l_list *list,
                          void *(*selector)(size_t *i, node_t *node,
                                            void *context),
                          void *context) {
  if (!list || !selector)
    return NULL;

  node_t *current = list->head;
  size_t i = 0;

  while (current) {
    void *result = selector(&i, current, context);
    if (result)
      return result;

    current = current->next;
    i++;
  }

  return NULL;
}

arr_t *find_all_at_linked_list(l_list *list,
                               void *(*selector)(size_t *i, node_t *node,
                                                 void *context),
                               void *context) {
  if (!list || !selector)
    return NULL;

  arr_t *arr = arr_create(2);

  node_t *current = list->head;
  size_t i = 0;
  void *last_result = NULL;

  while (current) {
    void *result = selector(&i, current, context);
    if (result)
      arr_push(arr, result);

    current = current->next;
    i++;
  }

  return arr;
}
