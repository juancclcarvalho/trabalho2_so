#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <thread.h>
#include <util.h>
#include <inttypes.h>

int tid_global = 0;
uint64_t current_running_start; // guarda o tempo onde uma determinada thread iniciou sua execução

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
	// seta TID da thread
	main_thread->TID = tid_global++;
	// inicia variavel que guarda tempo da cpu
	main_thread->cpu_time = 0;
	// recebe o tempo de inicio de execução da main 
	current_running_start = get_timer();
	
	return 0;
}

// TODO: creates a new thread and inserts in the ready queue.
int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg)
{
	// cria tcb para a nova thread
	tcb_t* new_thread = (tcb_t*)malloc(sizeof(tcb_t));
	// coloca o exit_handler no ultimo indice da pilha, por conta do ret, exit_handler vai ser executado primeiro, sempre
	new_thread->stack[STACK_SIZE - 1] = &exit_handler;
	// campo rsp da nova tcb aponta pro ultimo indice da pilha
	new_thread->rsp = &new_thread->stack[STACK_SIZE - 1];
	// arg fica no rdi que é o registrador de indice 9
	new_thread->registers[9] = arg;
	// definir status_t(enum) da tcb como ready
	new_thread->status = FIRST_TIME;
	// seta TID da thread
	new_thread->TID = tid_global++;
	// guarda endereço da rotina a ser executada, esse ponteiro vai ser utilizado pelo exit_handler
	new_thread->start_routine = start_routine;
	// inicia variavel que guarda tempo da cpu
	new_thread->cpu_time = 0;
	// envia o ponteiro do tcb para a estrutura thread recebida pelo usuario
	thread->tcb = new_thread;

	// cria node_t para a thread e insere na ready_queue
	node_t* node = node_init(new_thread);
	enqueue(&ready_queue, node, PRIORITY);
	
	return 0;
}

// TODO: yields the CPU to another thread
int thread_yield()
{
	// recebe o tempo de saida de uma thread
	uint64_t exit_time = get_timer();
	
	// atualiza o tempo que uma thread ocupou a cpu e seta seu status como ready
	current_running->cpu_time += (exit_time - current_running_start); 
	current_running->status = READY;

	// insere current_running de volta a ready queue e realiza a troca de contexto
	node_t* node = node_init(current_running);
	enqueue(&ready_queue, node, PRIORITY);
	scheduler_entry();

	return 0;
}

// TODO: waits for a thread to finish
int thread_join(thread_t *thread, int *retval) 
{
	tcb_t * tcb = thread->tcb;

	// enquanto status da thread de parametro != exited
	while(tcb->status != EXITED)
		thread_yield();

	// retval eh o valor de retorno da thread passada por parametro
	if (retval != NULL)
		*retval = tcb->registers[14]; // valor de retorno fica no $rax
	
	return 0;
}

// TODO: marks a thread as EXITED and terminates the thread
void thread_exit(int status) // não sabemos pra que serve o 'int status' xD
{
	// altera o estado da thread atual para EXITED
	current_running->status = EXITED;
	// realiza a troca de contexto sem inserir current_running para a ready queue
	scheduler_entry();
}

// TODO: selects the next thread to execute
void scheduler()
{
	// recebe o primeiro nó da ready queue
	node_t* node = dequeue(&ready_queue);
	// altera o ponteiro current_running para a tcb do nó retirado
	current_running = node->tcb;
	// altera o status da thread prestes a rodar para RUNNING
	current_running->status = RUNNING;
	// atualiza o tempo de inicio de execução de uma thread
	current_running_start = get_timer();
}

// TODO: you must  make sure this function is called  if a thread does
// not call thread_exit
/*
	Exit handler é a PRIMEIRA função a ser executada por todas as threads da biblioteca (exceto a main)
	seu propósito é:
	---------------> desviar execução para rotina inserida pelo usuário
	---------------> caso retorne dessa rotina, exit_handler sempre chama thread_exit()

	assim garantimos a condição do 'TODO' acima
*/
void exit_handler(void *arg)
{
	current_running->start_routine(arg);
	thread_exit(0);
}