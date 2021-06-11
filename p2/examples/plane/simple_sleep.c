#include <unistd.h>

#include <threadu.h>
#include "util.h"

void *simple_sleep(void *p)
{
	int sleep_time = *(int *)p;
	
	sleep_time *= 1000;
	while (1) {
		print_str(25, 0, "Thread 3 (Simple)    : will SLEEP!");
		usleep(sleep_time);
		print_str(25, 0, "Thread 3 (Simple)    : will YIELD!");
		thread_yield();		
	}
	thread_exit(1);
}

