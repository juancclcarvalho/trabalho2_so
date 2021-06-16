#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <threadu.h>
#include "util.h"

unsigned long long saida;

void f1()
{
    saida = get_timer();
    thread_exit(1);
}

int main()
{
    unsigned long long inicio;
    thread_t* thr = (thread_t*)malloc(sizeof(thread_t));
    thread_init();
    thread_create(thr, &f1, NULL);
    inicio = get_timer();
    thread_yield();
    printf("Tempo de troca de contexto == %llu\n", saida - inicio);
}