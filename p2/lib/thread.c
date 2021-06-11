#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <queue.h>
#include <thread.h>

node_t	ready_queue;
tcb_t	*current_running;

int tid_global = 0;

/*
  TODO:  thread_init: initializes  the  thread library  and creates  a
  thread for  the main function. Returns  0 on success, or  -EINVAL if
  the library has already been initialized.
 */
int thread_init()
{
	return 0;
}

// TODO: creates a new thread and inserts in the ready queue.
int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg)
{
	return 0;
}

// TODO: yields the CPU to another thread
int thread_yield()
{
	return 0;
}

// TODO: waits for a thread to finish
int thread_join(thread_t *thread, int *retval) 
{
	return 0;
}

// TODO: marks a thread as EXITED and terminates the thread
void thread_exit(int status)
{
}

// TODO: selects the next thread to execute
void scheduler()
{
}

// TODO: you must  make sure this function is called  if a thread does
// not call thread_exit
void exit_handler()
{
}

