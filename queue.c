#include "queue.h"
#include <stdbool.h>
#include <string.h>

queue_t *new_queue(size_t capacity) {
  if (capacity == 0)
    return NULL;

  queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
  if (!queue)
    return NULL;

  queue->q = (void **)malloc(sizeof(void *) * capacity);
  if (!queue->q) {
    free(queue);
    return NULL;
  }

  queue->capacity = capacity;
  queue->count = 0;
  queue->front = 0;
  queue->rear = 0;

  return queue;
}

void free_queue(queue_t *queue) {
  if (!queue)
    return;

  if (queue->q)
    free(queue->q);
  free(queue);
}

void resize_queue(queue_t *queue) {
  if (!queue || !queue->q)
    return;

  size_t new_capacity = queue->capacity * 2;
  void **new_q = (void **)malloc(sizeof(void *) * new_capacity);
  if (!new_q)
    return;

  size_t j = 0;
  for (size_t i = queue->front; i != queue->rear;
       i = (i + 1) % queue->capacity) {
    new_q[j++] = queue->q[i];
  }

  free(queue->q);
  queue->q = new_q;
  queue->front = 0;
  queue->rear = queue->count;
  queue->capacity = new_capacity;
}

void enqueue(queue_t *queue, void *item) {
  if (!queue || !queue->q || !item)
    return;

  if (queue->count == queue->capacity) {
    resize_queue(queue);
  }

  queue->q[queue->rear] = item;
  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->count++;
}

void *dequeue(queue_t *queue) {
  if (!queue || !queue->q || queue->count == 0)
    return NULL;

  void *item = queue->q[queue->front];
  queue->front = (queue->front + 1) % queue->capacity;
  queue->count--;

  return item;
}

void *peek(queue_t *queue) {
  if (!queue || !queue->q || queue->count == 0)
    return NULL;

  return queue->q[queue->front];
}

bool is_queue_empty(queue_t *queue) {
  if (!queue)
    return true;

  return queue->count == 0;
}

size_t queue_size(queue_t *queue) {
  if (!queue)
    return 0;

  return queue->count;
}
