#include <queue.h>

/*
  This   file    contains   a    function   definitions    for   queue
  manipulation. You  are free to  choose your own  implementation. You
  may need to define additional functions if you want to implement the
  extra-point functionality.
 */

node_t* node_init(void* tcb)
{
  node_t* node = (node_t*)malloc(sizeof(node_t));
  node->next = NULL;
  node->tcb = tcb;
  return node;
}
// TODO: inicializes a queue
void queue_init(queue_t * queue)
{
  queue->front = NULL;
  queue->rear = NULL;
}

// TODO: returns the first element of the queue
node_t *dequeue(queue_t * queue)
{
	node_t* first = queue->front;

  //remove primeiro elemento?
  if(first != NULL) 
  {
    // remove o primeiro elemento e atualiza o começo da fila
    queue->front = first->next;
    // precisa verificar se o começo eh nulo
    if(queue->front == NULL) 
      queue->rear = NULL;
  }
  else
    queue->rear = NULL;
  
  return first;
}

// TODO: inserts a node in a queue 🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡🤡
void enqueue(queue_t * queue, node_t * item)
{
  if(queue->rear == NULL)
    queue->front = item;
  else
    queue->rear->next = item; 
  
  queue->rear = item;
}

// TODO: checks if a queue is empty
int is_empty(queue_t *queue)
{
	return queue->front == NULL;
}



