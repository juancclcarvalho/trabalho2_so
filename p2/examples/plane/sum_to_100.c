#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <threadu.h>
#include "util.h"

static void print_counter(int done);
static int rec(int n);

void sum_to_100(void *p)
{
	int i, sum;
	int sleep_time = *(int *)p;

	clear();
	sleep_time *= 1000;
	for (i = 0; i <= 100; i++) {
		print_str(15, 0, "Did you know that 1 + ... + ");
		sum = rec(i);
		gotoxy(29, 15);
		printf("%d = %d \n", i, sum);
		fflush(stdout);
		print_counter(FALSE);
		usleep(sleep_time);
		thread_yield();
	}
	print_counter(TRUE);
	thread_exit(0);
}

static void print_counter(int done)
{
	static int counter = 0;
	
	print_str(24, 0, "Thread 2 (Math)      : ");
	if (done) {
		print_str(24, 24, "Exited");
	} else {
		printf("%d ", counter++);
	}
}

/* calculate 1 + ... + n */
static int rec(int n)
{
	if (n % 37 == 0) {
		thread_yield();
	}
	if (n == 0) {
		return 0;
	} else {
		return n + rec(n - 1);
	}
}
