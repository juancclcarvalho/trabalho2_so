#ifndef THREADU_H
#define THREADU_H

typedef enum {
    FALSE, TRUE
} bool_t;

typedef struct thr {
	void 	*tcb;
} thread_t;

int thread_create(thread_t *thread, void *(*start_routine)(void *), void *arg);
int thread_yield();
int thread_join(thread_t *thread, int *retval); 
int thread_init();

void thread_exit(int status);

#endif /* THREADU_H */
