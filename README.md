# Stryktyrki 🚀

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen)](https://github.com/DilemaFixer/Stryktyrki)
[![Version](https://img.shields.io/badge/version-1.0.0-blue)](https://github.com/DilemaFixer/Stryktyrki)
[![License](https://img.shields.io/badge/license-MIT-green)](https://github.com/DilemaFixer/Stryktyrki)
[![Language](https://img.shields.io/badge/language-C-orange)](https://github.com/DilemaFixer/Stryktyrki)

A lightweight and efficient C library for structured data processing and manipulation.

## 📥 Installation

### Clone the entire repository

#### Unix-based systems (Linux, macOS)
```bash
mkdir -p ~/stryktyrki
cd ~/stryktyrki
git clone https://github.com/DilemaFixer/Stryktyrki.git .
```

#### Windows
```cmd
mkdir %USERPROFILE%\stryktyrki
cd %USERPROFILE%\stryktyrki
git clone https://github.com/DilemaFixer/Stryktyrki.git .
```

### Download individual components

#### Unix-based systems (Linux, macOS)
```bash
# Create directory for the components
mkdir -p ~/stryktyrki
cd ~/stryktyrki

# Core components
curl -o logger.h https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/logger.h
curl -o logger.c https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/logger.c

# Array dependency
curl -o arr.h https://raw.githubusercontent.com/DilemaFixer/Arr/main/arr.h
curl -o arr.c https://raw.githubusercontent.com/DilemaFixer/Arr/main/arr.c

# Individual data structures
curl -o linked_list.h https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/linked_list.h
curl -o linked_list.c https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/linked_list.c
curl -o mem_stack.h https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/mem_stack.h
curl -o mem_stack.c https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/mem_stack.c
curl -o queue.h https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/queue.h
curl -o queue.c https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/queue.c
curl -o stack.h https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/stack.h
curl -o stack.c https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/stack.c
```

#### Windows
```cmd
mkdir %USERPROFILE%\stryktyrki
cd %USERPROFILE%\stryktyrki

REM Core components
curl -o logger.h https://raw.githubusercontent.com/DilemaFixer/CSL/main/logger.h
curl -o logger.c https://raw.githubusercontent.com/DilemaFixer/CSL/main/logger.c

REM Array dependency
curl -o arr.h https://raw.githubusercontent.com/DilemaFixer/Arr/main/arr.h
curl -o arr.c https://raw.githubusercontent.com/DilemaFixer/Arr/main/arr.c

REM Individual data structures
curl -o linked_list.h https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/linked_list.h
curl -o linked_list.c https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/linked_list.c
curl -o mem_stack.h https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/mem_stack.h
curl -o mem_stack.c https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/mem_stack.c
curl -o queue.h https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/queue.h
curl -o queue.c https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/queue.c
curl -o stack.h https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/stack.h
curl -o stack.c https://raw.githubusercontent.com/DilemaFixer/Stryktyrki/main/stack.c
```

## 🔧 API and Usage Examples

### 📊 Data Structures

#### Array (arr_t)
A dynamic array implementation for efficient sequential data storage with automatic resizing.

##### Core Structures
```c
typedef struct {
    void** data;    // Array of void pointers for storing elements
    size_t size;    // Current number of elements in the array
    size_t capacity; // Total capacity of the array
} arr_t;
```

##### Functions
```c
arr_t* arr_create(size_t initial_capacity);
// Creates a new dynamic array with specified initial capacity

void arr_destroy(arr_t* arr);
// Frees all resources associated with the array

bool arr_push(arr_t* arr, void* element);
// Adds an element to the end of the array

void* arr_get(arr_t* arr, size_t index);
// Retrieves the element at the specified index

bool arr_set(arr_t* arr, size_t index, void* element);
// Sets the element at the specified index

bool arr_remove(arr_t* arr, size_t index);
// Removes the element at the specified index

size_t arr_size(arr_t* arr);
// Returns the number of elements in the array

bool arr_resize(arr_t* arr, size_t new_capacity);
// Resizes the array to the specified capacity
```

##### Usage Example
```c
#include "arr.h"
#include <stdio.h>

void example() {
    // Create a dynamic array with initial capacity of 8
    arr_t* myArray = arr_create(8);
    
    // Create and add some integer elements (must be heap-allocated for persistence)
    int* val1 = malloc(sizeof(int));
    int* val2 = malloc(sizeof(int));
    *val1 = 42;
    *val2 = 100;
    
    arr_push(myArray, val1);
    arr_push(myArray, val2);
    
    // Access elements
    int* retrieved = arr_get(myArray, 0);
    printf("First element: %d\n", *retrieved);
    
    // Get array size
    printf("Array size: %zu\n", arr_size(myArray));
    
    // Clean up (note: this doesn't free the contained elements)
    arr_destroy(myArray);
    free(val1);
    free(val2);
}
```

#### Linked List (l_list)
A singly linked list implementation for efficient node-based sequential data storage.

##### Core Structures
```c
typedef struct node_t {
    struct node_t* next; // Pointer to the next node in the list
} node_t;

typedef struct l_list {
    node_t* head;    // First node in the list
    size_t count;    // Number of nodes in the list
    void (*free_custom_node)(node_t *node); // Custom node freeing function
} l_list;
```

##### Functions
```c
l_list *new_empty_linked_list();
// Creates a new empty linked list

l_list *new_linked_list_with_node(node_t *node);
// Creates a linked list with an initial node

void free_linked_list(l_list *list);
// Frees all resources associated with the linked list

void linked_list_add_at(l_list *list, node_t *node, size_t index);
// Adds a node at the specified index

void linked_list_add_first(l_list *list, node_t *node);
// Adds a node at the beginning of the list

void linked_list_add_last(l_list *list, node_t *node);
// Adds a node at the end of the list

void linked_list_remove_at(l_list *list, size_t index);
// Removes the node at the specified index

void linked_list_remove_first(l_list *list);
// Removes the first node in the list

void linked_list_remove_last(l_list *list);
// Removes the last node in the list

void* find_at_linked_list(l_list *list, void* (*selector)(size_t *i, node_t *node, void *context), void *context);
// Finds a node using a selector function

arr_t* find_all_at_linked_list(l_list *list, void* (*selector)(size_t *i, node_t *node, void *context), void *context);
// Finds all nodes matching a criteria using a selector function
```

##### Usage Example
```c
#include "linked_list.h"
#include "logger.h"
#include <stdio.h>

// Example of a custom node type
typedef struct my_node {
    node_t base;      // Must be first to allow casting to node_t
    int value;
} my_node;

// Custom node freeing function
void free_my_node(node_t *node) {
    if (node) {
        free(node);
    }
}

// Selector function to find a node with a specific value
void* find_node_by_value(size_t *i, node_t *node, void *context) {
    my_node *custom_node = (my_node*)node;
    int target_value = *((int*)context);
    
    if (custom_node->value == target_value) {
        return custom_node;
    }
    return NULL;
}

void example() {
    // Create a linked list
    l_list *list = new_empty_linked_list();
    list->free_custom_node = free_my_node;
    
    // Create and add some nodes
    for (int i = 0; i < 5; i++) {
        my_node *node = malloc(sizeof(my_node));
        node->base.next = NULL;
        node->value = i * 10;
        linked_list_add_last(list, (node_t*)node);
    }
    
    // Find a node with value 20
    int search_value = 20;
    my_node *found = find_at_linked_list(list, find_node_by_value, &search_value);
    if (found) {
        printf("Found node with value: %d\n", found->value);
    }
    
    // Clean up
    free_linked_list(list);
}
```

#### Memory Stack (mem_stack)
A stack-based memory management structure for efficient fixed-size allocations.

##### Core Structures
```c
typedef struct mem_stack {
    void *mem;       // Base memory pointer
    size_t capacity; // Total capacity in bytes
    void* sp;        // Stack pointer (current position)
} mem_stack;
```

##### Functions
```c
mem_stack *new_mem_stack(size_t capacity);
// Creates a new memory stack with specified capacity in bytes

void free_mem_stack(mem_stack *stack);
// Frees all resources associated with the memory stack

void mem_stack_resize(mem_stack *stack, size_t plus_size);
// Resizes the memory stack by adding the specified additional size

void mem_stack_push(mem_stack *stack, void *item, size_t size);
// Pushes data of specified size onto the stack

void *mem_stack_pop(mem_stack *stack, size_t size);
// Pops data of specified size from the stack

void *mem_stack_peek(mem_stack *stack, size_t size);
// Peeks at data of specified size from the stack without removing it

bool is_mem_stack_empty(mem_stack *stack);
// Checks if the memory stack is empty
```

##### Usage Example
```c
#include "mem_stack.h"
#include <stdio.h>

void example() {
    // Create a memory stack with 1024 bytes capacity
    mem_stack *stack = new_mem_stack(1024);
    
    // Push integers onto the stack
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        mem_stack_push(stack, &values[i], sizeof(int));
    }
    
    // Peek at the top integer without removing it
    int *peeked = mem_stack_peek(stack, sizeof(int));
    printf("Top value (peek): %d\n", *peeked);
    
    // Pop integers from the stack in reverse order
    while (!is_mem_stack_empty(stack)) {
        int *popped = mem_stack_pop(stack, sizeof(int));
        printf("Popped value: %d\n", *popped);
    }
    
    // Clean up
    free_mem_stack(stack);
}
```

#### Queue (queue_t)
A circular buffer-based queue implementation for FIFO (First-In-First-Out) data operations.

##### Core Structures
```c
typedef struct queue_t {
   void **q;        // Array of void pointers for storing elements
   size_t count;    // Number of elements currently in the queue
   size_t capacity; // Total capacity of the queue
   size_t front;    // Index of the front element
   size_t rear;     // Index where the next element will be inserted
} queue_t;
```

##### Functions
```c
queue_t *new_queue(size_t capacity);
// Creates a new queue with specified capacity

void free_queue(queue_t *queue);
// Frees all resources associated with the queue

void resize_queue(queue_t *queue);
// Resizes the queue to double its current capacity

void enqueue(queue_t *queue, void *item);
// Adds an item to the back of the queue

void *dequeue(queue_t *queue);
// Removes and returns the item from the front of the queue

void *peek(queue_t *queue);
// Returns the item at the front of the queue without removing it

bool is_queue_empty(queue_t *queue);
// Checks if the queue is empty

size_t queue_size(queue_t *queue);
// Returns the number of elements in the queue
```

##### Usage Example
```c
#include "queue.h"
#include <stdio.h>

void example() {
    // Create a queue with capacity for 10 elements
    queue_t *queue = new_queue(10);
    
    // Create and enqueue some integer elements (must be heap-allocated for persistence)
    for (int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        *value = i * 10;
        enqueue(queue, value);
    }
    
    // Check the front of the queue without removing it
    int *front = peek(queue);
    if (front) {
        printf("Front of queue: %d\n", *front);
    }
    
    // Dequeue and process elements in FIFO order
    while (!is_queue_empty(queue)) {
        int *value = dequeue(queue);
        printf("Dequeued: %d\n", *value);
        free(value);
    }
    
    // Clean up
    free_queue(queue);
}
```

#### Array Stack (arr_stack)
A stack implementation backed by a dynamic array for LIFO (Last-In-First-Out) operations.

##### Core Structures
```c
typedef struct arr_stack {
    void **items;   // Array of void pointers for storing elements
    size_t capacity; // Total capacity of the stack
    size_t count;    // Current number of elements in the stack
} arr_stack;
```

##### Functions
```c
arr_stack *new_arr_stack(size_t capacity);
// Creates a new array stack with specified capacity

void free_arr_stack(arr_stack *stack);
// Frees all resources associated with the stack

void arr_stack_resize(arr_stack *stack);
// Resizes the stack to double its current capacity

void arr_stack_push(arr_stack *stack, void *item);
// Pushes an item onto the top of the stack

void *arr_stack_pop(arr_stack *stack);
// Removes and returns the item from the top of the stack

void *arr_stack_peek(arr_stack *stack);
// Returns the item at the top of the stack without removing it

bool is_arr_stack_empty(arr_stack *stack);
// Checks if the stack is empty
```

##### Usage Example
```c
#include "stack.h"
#include <stdio.h>

void example() {
    // Create a stack with capacity for 8 elements
    arr_stack *stack = new_arr_stack(8);
    
    // Create and push some integer elements (must be heap-allocated for persistence)
    for (int i = 0; i < 5; i++) {
        int *value = malloc(sizeof(int));
        *value = i * 10;
        arr_stack_push(stack, value);
    }
    
    // Peek at the top element without removing it
    int *top = arr_stack_peek(stack);
    if (top) {
        printf("Top of stack: %d\n", *top);
    }
    
    // Pop and process elements in LIFO order
    while (!is_arr_stack_empty(stack)) {
        int *value = arr_stack_pop(stack);
        printf("Popped: %d\n", *value);
        free(value);
    }
    
    // Clean up
    free_arr_stack(stack);
}
```

## 📚 Dependencies

- [Arr](https://github.com/DilemaFixer/Arr) - Dynamic array implementation
- [CSL](https://github.com/DilemaFixer/CSL) - C string list utilities
