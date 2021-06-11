#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <threadu.h>
#include "util.h"

#define ROWS 4
#define COLUMNS 18

static char picture[ROWS][COLUMNS + 1] = {
    "     ___       _  ",
    " | __\\_\\_o____/_| ",
    " <[___\\_\\_-----<  ",
    " |  o'            "
};

static void draw(int locx, int locy, int plane);
static void print_counter(void);

void *sum_to_100(void *p);
void *simple_sleep(void *p);

void *plane(void *p)
{
	int locx = 80, locy = 1;
	int sleep_time = *(int *)p;
	
	clear();
	sleep_time *= 1000;
	while (1) {
		print_counter();
		/* erase plane */
		draw(locx, locy, FALSE);
		locx -= 1;
		if (locx < -20) {
			locx = 80;
		}
		/* draw plane */
		draw(locx, locy, TRUE);
		print_counter();
		usleep(sleep_time);
		thread_yield();
	}
}

/* print counter */
static void print_counter(void)
{
	static int counter = 0;

	print_str(23, 0, "Thread 1 (Plane)     : ");
	printf("%d\n", counter++);
	fflush(stdout);
}

/* draw plane */
static void draw(int locx, int locy, int plane)
{
	int i, j;
    
	for (i = 0; i < COLUMNS; i++) {
		if ((locx + i) < 0)
			continue;
		for (j = 0; j < ROWS; j++) {
			/* draw plane */
			if (plane == TRUE) {
				print_char(locy + j, locx + i, picture[j][i]);
			}
			/* erase plane */
			else {
				print_char(locy + j, locx + i, ' ');
			}
		}
	}
}

int main(int argc, char *argv[])	
{
	int plane_sleep_time, sum_sleep_time, simple_sleep_time;
	thread_t thd1, thd2, thd3;
	
	if (argc != 4) {
		fprintf(stderr, "\nUsage: plane <plane_sleep_time> <sum_sleep_time> <simple_sleep_time>\n"
			"\tplane_sleep_time: air plane thread sleep time in milliseconds\n"
			"\tsum_sleep_time: sum thread sleep time in milliseconds\n"
			"\tSimple_sleep_time: simple thread sleep time in milliseconds\n\n");
		exit(1);
	}
	plane_sleep_time = atoi(argv[1]);
	sum_sleep_time = atoi(argv[2]);
	simple_sleep_time = atoi(argv[3]);
	
	thread_init();
	thread_create(&thd1, plane, &plane_sleep_time);
	thread_create(&thd2, sum_to_100, &sum_sleep_time);
	thread_create(&thd3, simple_sleep, &simple_sleep_time);
	thread_join(&thd1, NULL);
	thread_join(&thd2, NULL);
	thread_join(&thd3, NULL);
}
