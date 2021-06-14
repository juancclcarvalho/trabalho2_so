#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <queue.h>
#include <thread.h>

queue_t	ready_queue;
tcb_t	*current_running;

int tid_global = 0;

/*
  TODO:  thread_init: initializes  the  thread library  and creates  a
  thread for  the main function. Returns  0 on success, or  -EINVAL if
  the library has already been initialized.
 */
int thread_init()
{
	//printf("Começando thread_init()\n");
	if(current_running != 0)
		return -EINVAL;
	// incializa tcb pra main
	tcb_t* main_thread = (tcb_t*)malloc(sizeof(tcb_t));
	// inicializa ready queue
	queue_init(&ready_queue);
	// current running aponta pra tcb da main
	current_running = main_thread;
	// definir status_t(enum) da tcb como running
	main_thread->status = FIRST_TIME;
	main_thread->TID = tid_global++;
	//printf("  Iniciou biblioteca com sucesso\n");
	return 0;
}

// TODO: creates a new thread and inserts in the ready queue.
int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg)
{
	//printf("criando nova thread com arg == %lld\n", (long long int)start_routine);
	// cria tcb para a nova thread
	//printf("1\n");
	tcb_t* new_thread = (tcb_t*)malloc(sizeof(tcb_t));
	// coloca o start routine no ultimo indice da pilha, por conta do ret
	//printf("2\n");
	new_thread->stack[STACK_SIZE - 1] = start_routine;
	// campo rsp da nova tcb aponta pro ultimo indice da pilha
	//printf("3\n");
	new_thread->rsp = &new_thread->stack[STACK_SIZE - 1];
	// arg fica no rdi que é o registrador de indice 9
	//printf("4\n");
	new_thread->registers[9] = arg;
	// definir status_t(enum) da tcb como ready
	//printf("5\n");
	new_thread->status = FIRST_TIME;
	// criar node_t para a thread e inserir na ready_queue
	//printf("6\n");
	node_t* node = node_init(new_thread);
	//printf("7\n");
	enqueue(&ready_queue, node);
	new_thread->TID = tid_global++;
	thread->tcb = new_thread;
	//printf("  Conseguiu criar nova thread com sucesso, TID == %d\n", new_thread->TID);
	return 0;
}

// TODO: yields the CPU to another thread
int thread_yield()
{
	//printf("vai dar yield \n");
	current_running->status = READY;
	node_t* node = node_init(current_running);
	enqueue(&ready_queue, node);
	scheduler_entry();
	//printf(" conseguiu dar yield\n");
	return 0;
}

// TODO: waits for a thread to finish
int thread_join(thread_t *thread, int *retval) 
{
	//printf("tentando dar join ");
	tcb_t * tcb = thread->tcb;
	//printf("em == %d\n", tcb->TID);
	// enquanto status da thread de parametro != exited
	while(tcb->status != EXITED)
	{
		//printf("bglho nao terminou, vai dar yield\n");
		// yield
		thread_yield();
	}
	// retval eh o valor de retorno da thread passada por parametro
	if (retval != NULL)
		*retval = tcb->registers[14];
	//printf("  deu join\n");
	return 0;
}

// TODO: marks a thread as EXITED and terminates the thread
void thread_exit(int status)
{
	//printf("chamou thread_exit\n");
	// altera o estado da thread atual para EXITED
	// scheduler, status eh I N U T I L
	current_running->status = EXITED;
	scheduler_entry();
	//printf("terminou thread_exit\n");
}

// TODO: selects the next thread to execute
void scheduler()
{
	//printf("squédiu\n");
	node_t* node = dequeue(&ready_queue);
	current_running = node->tcb;
	//printf("current running == %llu\n", current_running);
	if (current_running->status != FIRST_TIME)
		current_running->stack[STACK_SIZE - 1] = &exit_handler;
	current_running->status = RUNNING;
	//printf("  sqúediu termionu e pah\n");
	//printf("%lu\n",sizeof(int));
}

// TODO: you must  make sure this function is called  if a thread does
// not call thread_exit
void exit_handler()
{
	//printf("ah ieie");
	thread_exit(0);
}

