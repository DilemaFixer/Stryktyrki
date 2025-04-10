#ifndef ARR_STACK_H
#define ARR_STACK_H

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
