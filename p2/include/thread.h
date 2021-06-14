#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include <threadu.h>

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
	// temos 8 bytes antes dos registradores
	uint64_t flags; // registrador de flags
	uint64_t registers[NUMBER_OF_REGISTERS];
	void* rsp;  // registrador do topo da pilha
	uint64_t* stack[STACK_SIZE];
	// TODO: define the fields for you TCB
} tcb_t;

#endif /* THREAD_H */
