#include <stdio.h>

#include <util.h>

void print_str(int line, int column, char *s)
{
	gotoxy(column, line);
	printf("%s", s);
	fflush(stdout);
}

void print_char(int y, int x, char c)
{
	gotoxy(x, y);
	printf("%c", c);
	fflush(stdout);
}

void print_int(int y, int x, int i)
{
	gotoxy(x, y);
	printf("%d", i);
	fflush(stdout);
}

