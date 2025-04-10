#ifndef MEM_STACK_H
#define MEM_STACK_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    LEVEL_FATAL = 0,
    LEVEL_WARN  = 1,
    LEVEL_DEBUG = 2,
    LEVEL_TODO  = 3,
    LEVEL_UNIMPLEMENTED = 4
} LogLevel;

static const char* const LEVEL_NAMES[] = {
    "FATAL", "WARN", "DEBUG", "TODO", "UNIMPLEMENTED"
};

static inline void lmessage(LogLevel level, const char* format, ...) {
    fprintf(stderr, "[%s] ", LEVEL_NAMES[level]);

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");

    if (level == LEVEL_FATAL || level == LEVEL_UNIMPLEMENTED) {
        exit(1);
    }
}

#define lfatal(...) lmessage(LEVEL_FATAL, __VA_ARGS__)
#define lwarn(...)  lmessage(LEVEL_WARN, __VA_ARGS__)
#define ldebug(...) lmessage(LEVEL_DEBUG, __VA_ARGS__)
#define ltodo(...)  lmessage(LEVEL_TODO, __VA_ARGS__)
#define lunimp(...) lmessage(LEVEL_UNIMPLEMENTED, "Not implemented: " __VA_ARGS__)

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
