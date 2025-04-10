#ifndef L_LIST
#define L_LIST

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "arr.h"

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
arr_t* find_all_at_linked_list(l_list *list, void* (*selector)(size_t *i, node_t *node, void *context), void *context);
#endif
