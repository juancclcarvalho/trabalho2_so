#include <lock.h>
#include <stdio.h>

enum {
      SPIN = FALSE,
};

// TODO: inicializes a lock
void lock_init(lock_t * l)
{
	if (SPIN) {
		l->status = UNLOCKED;
	} else {
		// inicializa a fila de threads travadas
		queue_t* q = (queue_t*) malloc(sizeof(queue_t));
		queue_init(q);
		l->q = q;
		l->status = UNLOCKED;
	}
}

// TODO:  acquires a  lock if  it is  available or  blocks the  thread
// otherwise
void lock_acquire(lock_t * l)
{
	if (SPIN) {
		while (LOCKED == l->status)
			thread_yield();
		l->status = LOCKED;
	} else {
		if(LOCKED == l->status)
			block(l);  // bloqueia a thread
		l->status = LOCKED; // bloqueia o lock
	}
}

// TODO:  releases a  lock  and  unlocks one  thread  from the  lock's
// blocking list
void lock_release(lock_t * l)
{
	if (SPIN) {
		l->status = UNLOCKED;
	} else {
		if (l->q->rear == NULL) // SE A LISTA DE THREADS ESPERANDO O LOCK ESTIVER VAZIA
			l->status = UNLOCKED; // O LOCK é destravado
		else
			unblock(l);	// a THREAD no começo da fila é destravada
	}
}

// TODO: blocks the running thread
void block(lock_t * l)
{
	enqueue(l->q, node_init(current_running), 0); // insere a thread na fila de threads bloqueadas pelo lock l
	current_running->status = LOCKED; // altera o status da thread
	scheduler_entry(); // <--- isso vai fazer a troca de contexto, e NÂO inserir a thread travada na ready queue
}

// TODO: unblocks  a thread that is waiting on a lock.
void unblock(lock_t *l)
{
	node_t* released_thread = dequeue(l->q); // retira a thread da fila de threads bloqueadas pelo lock l
	enqueue(&ready_queue, released_thread, PRIORITY); // retorna essa thread para a ready queue
	tcb_t* tcb = released_thread->tcb; 
	tcb->status = READY; // seta o status da thread como ready
}