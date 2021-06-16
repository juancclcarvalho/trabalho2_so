#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <thread.h>
#include <util.h>

int tid_global = 0;
unsigned long long current_running_start;

/*
  TODO:  thread_init: initializes  the  thread library  and creates  a
  thread for  the main function. Returns  0 on success, or  -EINVAL if
  the library has already been initialized.
 */
int thread_init()
{
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
	main_thread->cpu_time = 0;
	current_running_start = get_timer();
	return 0;
}

// TODO: creates a new thread and inserts in the ready queue.
int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg)
{
	//printf("criando nova thread com arg == %lld\n", (long long int)start_routine);
	// cria tcb para a nova thread
	tcb_t* new_thread = (tcb_t*)malloc(sizeof(tcb_t));
	// coloca o start routine no ultimo indice da pilha, por conta do ret
	new_thread->stack[STACK_SIZE - 1] = &exit_handler;
	// campo rsp da nova tcb aponta pro ultimo indice da pilha
	new_thread->rsp = &new_thread->stack[STACK_SIZE - 1];
	// arg fica no rdi que é o registrador de indice 9
	new_thread->registers[9] = arg;
	// definir status_t(enum) da tcb como ready
	new_thread->status = FIRST_TIME;
	// criar node_t para a thread e inserir na ready_queue
	node_t* node = node_init(new_thread);
	enqueue(&ready_queue, node, PRIORITY);
	new_thread->TID = tid_global++;
	new_thread->start_routine = start_routine;
	new_thread->cpu_time = 0;
	thread->tcb = new_thread;
	
	//printf("  Conseguiu criar nova thread com sucesso, TID == %d\n", new_thread->TID);
	return 0;
}

// TODO: yields the CPU to another thread
int thread_yield()
{
	unsigned long long exit_time = get_timer();
	current_running->cpu_time += (exit_time - current_running_start); 
	current_running->status = READY;
	node_t* node = node_init(current_running);
	enqueue(&ready_queue, node, PRIORITY);
	scheduler_entry();

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
	current_running->status = RUNNING;
	//printf("  sqúediu termionu e pah\n");
}

// TODO: you must  make sure this function is called  if a thread does
// not call thread_exit
void exit_handler(void *arg)
{
	//printf("vai rodar a funcao\n");
	current_running_start = get_timer();
	current_running->start_routine(arg);
	//printf("ah ieie\n");
	thread_exit(0);
}

