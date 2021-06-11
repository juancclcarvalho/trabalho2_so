#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <x86intrin.h>
#include <stdint.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))


void print_str(int line, int column, char *s);
void print_char(int y, int x, char c);
void print_int(int line, int column, int i);

static inline uint64_t get_timer(void)
{
	return __rdtsc();
}

#endif /* UTIL_H */
