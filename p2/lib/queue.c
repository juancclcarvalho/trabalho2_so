#include <thread.h>
#include <stdio.h>

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

  //remove primeiro elemento
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
void enqueue(queue_t * queue, node_t * item, int priority)
{
  if(priority)
    enqueue_sort(queue, item, lt);
  else
  {
    if(queue->rear == NULL)
      queue->front = item;
    else
      queue->rear->next = item; 
  
    queue->rear = item;
  }
}

// TODO: checks if a queue is empty
int is_empty(queue_t *queue)
{
	return queue->front == NULL;
}

int lt(node_t *a, node_t *b)
{
  if (a == NULL || b == NULL) return 1;
  tcb_t* a_tcb = a->tcb;
  tcb_t* b_tcb = b->tcb;
  printf("comparando prioridades\n");
  printf("  a == %llu, a TID == %d\n  b == %llu, b TID ==%d\n  resultado == %u\n", a_tcb->cpu_time,a_tcb->TID, b_tcb->cpu_time, b_tcb->TID, a_tcb->cpu_time < b_tcb->cpu_time);
  return a_tcb->cpu_time < b_tcb->cpu_time;
}


void enqueue_sort(queue_t *q, node_t *item, node_lte comp)
{
  node_t *p1, *p2;
  p1 = q->front;
  p2 = NULL;

  // insere no começo
  if (comp(item, p1))
  {
    item->next = p1;
    q->front = item;
    return;
  }

  p2 = p1;
  p1 = p1->next;

  while (comp(item, p1) && p1 != NULL)
  {
    p2 = p1;
    p1 = p1->next;
  }

  if(p1 != NULL) // insere no meio
  {
    item->next = p1;
    p2->next = item;
  }
  else // insere no fim
  {
    p2->next = item;
  }
}