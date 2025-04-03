#ifndef ARR_STACK_H
#define ARR_STACK_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct arr_stack {
    void **items;
    size_t capacity;
    size_t count;
} arr_stack;

arr_stack *new_arr_stack(size_t capacity);
void free_arr_stack(arr_stack *stack);
void arr_stack_resize(arr_stack *stack);
void arr_stack_push(arr_stack *stack , void *item);
void *arr_stack_pop(arr_stack *stack);
void *arr_stack_peek(arr_stack *stack);
bool is_arr_stack_empty(arr_stack *stack);

#endif
