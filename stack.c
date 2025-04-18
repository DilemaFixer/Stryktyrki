#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

arr_stack *new_arr_stack(size_t capacity) {
  if (capacity == 0)
    lfatal("Can't create stack with zero capacity");

  arr_stack *stack = (arr_stack *)malloc(sizeof(arr_stack));
  if (!stack)
    lfatal("Error allocation memory for stack struct");

  stack->items = malloc(sizeof(void *) * capacity);
  if (!stack->items) {
    free(stack);
    lfatal("Error allocation mempry for stack_t -> items ");
  }

  stack->capacity = capacity;
  stack->count = 0;
  return stack;
}

void free_arr_stack(arr_stack *stack) {
  if (!stack)
    return;

  if (stack->items)
    free(stack->items);

  free(stack);
}

void arr_stack_resize(arr_stack *stack) {
  if (!stack)
    lfatal("Can't resize stack, ptr on it is NULL");
  if (!stack->items)
    lfatal("Can't resize stack, ptr on items is NULL");
  size_t new_capacity = stack->capacity * 2;
  void **buffer = malloc(new_capacity * sizeof(void *));
  if (!buffer)
    lfatal("Failed to allocate memory for arr_stack resize");
  if (stack->count != 0)
    memcpy(buffer, stack->items, stack->count * sizeof(void *));
  free(stack->items);
  stack->items = buffer;
  stack->capacity = new_capacity;
}

void arr_stack_push(arr_stack *stack, void *item) {
  if (!stack)
    lfatal("Can't push item to stack , ptr to stack is NULL");
  if (!item)
    lfatal("Can't push item to stack , item ptr is NULL");

  if (stack->count + 1 > stack->capacity)
    arr_stack_resize(stack);

  stack->items[stack->count] = item;
  stack->count++;
}
void *arr_stack_pop(arr_stack *stack) {
  if (!stack)
    lfatal("Can't pop item from stack, stack ptr is NULL");
  if (stack->count == 0)
    return 0;
  stack->count--;
  return stack->items[stack->count];
}

void *arr_stack_peek(arr_stack *stack) {
  if (!stack)
    lfatal("Can't peek item from stack, ptr on it is NULL");
  if (stack->count == 0)
    return NULL;
  return stack->items[stack->count - 1];
}

bool is_arr_stack_empty(arr_stack *stack) {
  if (!stack)
    return true;
  return (stack->count == 0 || stack->items == NULL);
}
