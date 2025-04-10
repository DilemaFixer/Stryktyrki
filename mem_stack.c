#include "mem_stack.h"
#include <stddef.h>
#include <string.h>

mem_stack *new_mem_stack(size_t capacity) {
  if (capacity == 0)
    lfatal("Can't create mem stack with zero capacity");
  mem_stack *stack = (mem_stack *)malloc(sizeof(mem_stack));
  if (!stack)
    lfatal("Error allocation memory for mem_stack struct");
  stack->mem = malloc(capacity * sizeof(char));
  if (!stack->mem)
    lfatal("Error allocation mempry for mem_stack -> mem");
  stack->capacity = capacity;
  stack->sp = stack->mem;
  return stack;
}
void free_mem_stack(mem_stack *stack) {
  if (!stack)
    return;
  if (stack->mem)
    free(stack->mem);
  free(stack);
}
void mem_stack_resize(mem_stack *stack, size_t plus_size) {
  if (!stack)
    lfatal("Can't resize mem_stack with null ptr on it");
  if (!stack->mem)
    lfatal("Can't resize mem_stack with null ptr on mem_stack -> mem");
  size_t new_capacity = (stack->capacity + plus_size) * 2;
  void *buffer = malloc(new_capacity * sizeof(char));
  if (!buffer)
    lfatal("Error allocation memory for resize mem_stack with new size %zu",
           new_capacity);
  if (stack->sp != stack->mem)
    memcpy(buffer, stack->mem, stack->capacity);

  ptrdiff_t sp_offset = (char *)stack->sp - (char *)stack->mem;
  free(stack->mem);
  stack->mem = buffer;
  stack->sp = (char *)buffer + sp_offset;
  stack->capacity = new_capacity;
}
void mem_stack_push(mem_stack *stack, void *item, size_t size) {
  if (!stack)
    lfatal("Can't push item to mem_stack with NULL ptr on it");
  if (!stack->mem)
    lfatal("Can't push item to mem_stack with NULL ptr on mem_stack -> mem");
  if (!stack->sp)
    lfatal(
        "Can't push item to mem_stack , stack pointer is null , mem_stack -> "
        "sp");
  if (size == 0)
    lfatal("Can't push item with zero size to mem_stack");
  if (!item)
    lfatal("Can't push item to mem_stack , item ptr is NULL");
  ptrdiff_t sp_offset = (char *)stack->sp - (char *)stack->mem;
  if (sp_offset + size > stack->capacity)
    mem_stack_resize(stack, size);
  memcpy(stack->sp, item, size);
  stack->sp = (char *)stack->sp + size;
}
void *mem_stack_pop(mem_stack *stack, size_t size) {
  if (!stack)
    lfatal("Can't pop item from mem_stack , ptr on it is NULL");
  if (!stack->sp)
    lfatal(
        "Can't pop item from mem_stack , stack pointer is null , mem_stack -> "
        "sp");
  if (size == 0)
    lfatal("Can't pop item with size zero from mem_stack");
  if (stack->capacity < size)
    lfatal("Can't pop item with size more that mem_stack capacity . %zu < %zu",
           stack->capacity, size);

  stack->sp = (char *)stack->sp - size;
  return stack->sp;
}
void *mem_stack_peek(mem_stack *stack, size_t size) {
  if (!stack)
    lfatal("Can't peek item from mem_stack , ptr on it is NULL");
  if (!stack->sp)
    lfatal("Can't peek item from mem_stack , stack pointer is null , mem_stack "
           "-> sp");
  if (size == 0)
    lfatal("Can't peek item with size zero from mem_stack");
  if (stack->capacity < size)
    lfatal("Can't peek item with size more that mem_stack capacity . %zu < %zu",
           stack->capacity, size);
  void *peek_ptr = (char *)stack->sp - size;
  return peek_ptr;
}
bool is_mem_stack_empty(mem_stack *stack) {
  if (!stack)
    return true;
  return (stack->sp == stack->mem || stack->mem == NULL);
}
