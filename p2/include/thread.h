#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include <threadu.h>
#include <queue.h>

#define NUMBER_OF_REGISTERS	15
#define STACK_SIZE		2048

void scheduler_entry();
void exit_handler();

typedef enum {
	      FIRST_TIME,
		  RUNNING,
	      READY,
	      BLOCKED,
	      EXITED
} status_t;

typedef struct tcb {
	int TID; // 4 bytes
	status_t status; //4 bytes
	void *(*start_routine)(void *); // 8 bytes
	uint64_t cpu_time; // 8 bytes
	uint64_t lixo; // 8 bytes
	// temos 8 bytes antes dos registradores
	uint64_t flags; // registrador de flags
	uint64_t registers[NUMBER_OF_REGISTERS];
	void* rsp;  // registrador do topo da pilha
	uint64_t* stack[STACK_SIZE];
	//int lixo[100];
	
	// TODO: define the fields for you TCB
} tcb_t;

enum {
    PRIORITY = TRUE,
};

queue_t	ready_queue;
tcb_t	*current_running;

#endif /* THREAD_H */
