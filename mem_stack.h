#ifndef MEM_STACK_H
#define MEM_STACK_H
#include <stdlib.h>
#include <stdbool.h>
typedef struct mem_stack {
    void *mem;
    size_t capacity;
    void* sp;
} mem_stack;
mem_stack *new_mem_stack(size_t capacity);
void free_mem_stack(mem_stack *stack);
void mem_stack_resize(mem_stack *stack , size_t plus_size);
void mem_stack_push(mem_stack *stack , void *item , size_t size);
void *mem_stack_pop(mem_stack *stack , size_t size);
void *mem_stack_peek(mem_stack *stack , size_t size);
bool is_mem_stack_empty(mem_stack *stack);
#endif
