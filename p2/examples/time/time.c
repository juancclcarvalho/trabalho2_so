#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <threadu.h>
#include <inttypes.h>
#include "util.h"

/*
    ESSE ARQUIVO SERVE PARA MEDIR O TEMPO GASTO PARA A TROCA DE CONTEXTO
    apenas guardamos o tempo antes e depois de dar yield na main
    e imprimimos o resultado.
*/

uint64_t saida;

void *f1()
{
    saida = get_timer();
    thread_exit(1);
    return NULL;
}

int main()
{
    uint64_t inicio;
    thread_t* thr = (thread_t*)malloc(sizeof(thread_t));
    thread_init();
    thread_create(thr, f1, NULL);
    inicio = get_timer();
    thread_yield();
    printf("Tempo de troca de contexto == %" PRIu64 "\n", saida - inicio);
}