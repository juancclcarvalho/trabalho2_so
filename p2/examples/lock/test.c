/*
  Simple programs to check the functionality of lock_acquire(),
  and lock_release().
*/

#include <stdlib.h>
#include <unistd.h>

#include <lock.h>
#include <util.h>
#include <threadu.h>

#define RUNNING 0
#define OK 1
#define FAILED 2
#define DONE 3

int shared_var = 0;
int exit_count = 0;             /* number of threads that have exited */
volatile int init = FALSE;      /* is lock l initialized */

lock_t l;

static void print_counter(int thread, int status);

void *thread2(void *p)
{
	int tmp, i;

	/* This thread initializes the lock, the other thread waits for init to 
	 * become true */
	if (!init) {
		lock_init(&l);
		init = TRUE;
	}
	/* Do some testing */
	for (i = 0; i < 100; i++) {
		/* Acquire lock before using shared_var */
		lock_acquire(&l);

		tmp = shared_var;
		/* Give thread3 a chance to run */
		if (i % 13 == 0) {
			/* Yielding inside the critical section  might trigger some 
			 * errors in bad implementations of the locks. */
			thread_yield();
		}
		/* shared_var should be equal to tmp. If the synchronization 
		 *  primitives are not working correctly then shared_var > tmp, 
		 *  because thread3 has increased shared_var. 
		 */
		shared_var = tmp + 1;

		/* Done using shared_var */
		lock_release(&l);
		print_counter(2, RUNNING);
		/* Give thread3 a chance to run */
		thread_yield();
	}

	exit_count++;

	/* When both threads have finished, print the result */
	if (exit_count == 2) {
		print_counter(2, (shared_var == 200) ? OK : FAILED);
	} else {
		print_counter(2, DONE);
	}
	thread_exit(0);
}

void *thread3(void *p)
{
	int tmp, i;

	/* Wait until thread2 initializes the lock */
	if (!init) {
		lock_init(&l);
		init = TRUE;
	}
	/* Do some testing */
	for (i = 0; i < 100; i++) {
		/* Acquire lock before using shared_var */
		lock_acquire(&l);
		tmp = shared_var;
		/* give thread2 a chance to run */
		if (i % 17 == 0) {
			/* Yielding inside the critical section  might trigger some 
			 * errors in bad implementations of the locks. */
			thread_yield();
		}
		/* shared_var should be equal to tmp. If the synchronization 
		 *  primitives are not working correctly then shared_var > tmp, 
		 *  because thread2 has increased shared_var. 
		 */
		shared_var = tmp + 1;
		/* Done using shared_var */
		lock_release(&l);
		print_counter(3, RUNNING);
		/* Give thread2 a chance to run */
		thread_yield();
	}
	exit_count++;

	/* When both threads have finished, print the result */
	if (exit_count == 2) {
		print_counter(3, (shared_var == 200) ? OK : FAILED);
	} else {
		print_counter(3, DONE);
	}
	thread_exit(0);
}

static void print_counter(int thread, int status)
{
	static int counter2 = 0, counter3 = 0;
	int line = 19 + thread;

	if (thread == 2) {
		print_str(21, 0, "Thread  2 (lock)      : ");
	} else {
		print_str(22, 0, "Thread  3 (lock)      : ");
	}
	usleep(20000);
	switch (status) {
	case RUNNING:
		if (thread == 2) {
			print_int(21, 25, counter2++);
		} else {
			print_int(22, 25, counter3++);
		}
		break;
	case DONE:
		print_str(line, 25, "Exited");
		break;
	case OK:
		print_str(line, 25, "Passed");
		break;
	default:
		print_str(line, 25, "Failed");
		break;
	}
}

int main()
{
	int rv;
	thread_t t1, t2;
	
	thread_init();
	
	clear();
	
	thread_create(&t1, thread2, NULL);
	thread_create(&t2, thread3, NULL);

	print_str(25, 25, "\n");
	
	thread_join(&t1, &rv);
	thread_join(&t2, &rv);
}
