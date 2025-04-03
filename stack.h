#ifndef ARR_STACK_H
#define ARR_STACK_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct arr_stack {
    void **items;
    size_t capacity;
    size_t count;
} arr_stack;

arr_stack *new_stack(size_t capacity);
void free_stack(arr_stack *stack);
void stack_resize(arr_stack *stack);
void stack_push(arr_stack *stack , void *item);
void *stack_pop(arr_stack *stack);
void *stack_peek(arr_stack *stack);
bool is_stack_empty(arr_stack *stack);

#endif
