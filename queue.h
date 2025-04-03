#ifndef QUEUE_H
#define QUEUE_H
#include <stdlib.h>
#include <stdbool.h>
typedef struct queue_t{
   void **q;
   size_t count;
   size_t capacity;
   size_t front;
   size_t rear;
} queue_t;
queue_t *new_queue(size_t capacity);
void free_queue(queue_t *queue);
void resize_queue(queue_t *queue);
void enqueue(queue_t *queue, void *item);
void *dequeue(queue_t *queue);
void *peek(queue_t *queue);
bool is_queue_empty(queue_t *queue);
size_t queue_size(queue_t *queue);
#endif
