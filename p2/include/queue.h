#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdlib.h>


struct node {
   struct node* next;
   void* tcb;
};

typedef struct node node_t;

typedef struct queue {
   node_t* front;
   node_t* rear;
} queue_t;

node_t* node_init();

/* Initialize a queue */
void queue_init(queue_t * queue);

/* Remove and return the item at the front of the queue Return NULL if the
   queue is empty */
node_t *dequeue(queue_t * queue);

/* Add item to the back of the queue */
void enqueue(queue_t * queue, node_t * item);

/* Determine if the queue is empty.
 * Returns 1 if the queue is empty.
 * Returns 0 otherwise.
 */
int is_empty(queue_t *queue);

/* Returns the first item in the queue
 * Returns NULL if the queue is empty
 */
node_t *peek(queue_t *queue);

/* A comparison function should return:
 *  1 if a is less-than-or-equal-to b;
 *  0 otherwise.
 */
typedef int (*node_lte)(node_t *a, node_t *b);

/* Insert this item /elt/ into the queue /q/
 * in ascending order with the less-than-or-equal-to
 * inequality /comp/.
 * If /q/ was sorted (w.r.t. /comp/) before the
 * call, then /q/ is sorted after the call.
 * This is the simple linear-time algorithm.
 */
void enqueue_sort(queue_t *q, node_t *item, node_lte comp);

#endif                          /* QUEUE_H */
