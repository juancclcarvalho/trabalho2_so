#include <stdio.h>
#include <unistd.h>
#include <threadu.h>
#include <math.h>

#include <util.h>

/*
    ESSE ARQUIVO SERVE PARA TESTAR O ESCALONADOR POR PRIORIDADES DE TEMPO DE CPU
    
    Temos três threads competindo pela CPU e três tarefas diferentes (f1,f2,f3)
    
    As funções são basicamente idênticas. A diferença entre elas é a quantidade que os laços são executados

    --> f1 chama yield três vezes, e cada vez que é escalonada, roda o laço interno DEZ MIL VEZES.
    --> f2 chama yield setenta vezes, e cada vez que é escalonada, roda o laço interno CEM VEZES.
    --> f3 chama yield cem vezes, e cada vez que é escalonada, roda o laço interno DEZ vezes.

    Se o código do escalonador estiver correto. F1 vai ser escalonado com a menor frequencia
    f2 vai ser escalonada mais frequentemente que f1
    e f3 vai ser escalonada com bastante frequencia (mais que as outras)
*/

void *f1()
{
	int i, j;
    double k;
    for(i = 0; i < 3; i++)
    {
        printf("============RODANDO F1============\n");
        for (j = 0; j < 10000; j++) 
        {
           k = log(i-j);
        }
        thread_yield();
    }
	thread_exit(k);
    return NULL;
}

void *f2()
{
	int i, j;
    double k;
    for(i = 0; i < 70; i++)
    {
        printf("==RODANDO F2==\n");
        for (j = 0; j < 100; j++) 
        {
        	k = log(i-j);
        }
        thread_yield();
    }
	thread_exit(k);
    return NULL;
}

void *f3()
{
	int i, j;
    double k;
    for( i = 0; i < 100; i++)
    {
        printf("RODANDO F3\n");
        for (j = 0; j < 10; j++) 
        {
           k = log(i-j);
        }
        thread_yield();
    }
	thread_exit(k);
    return NULL;
}

int main()
{
	thread_t thd[3];
    int i;

	thread_init();
	printf("BEGIN: Time stamp: %ld\n", get_timer());

	thread_create(&thd[0], f1, NULL);
    thread_create(&thd[1], f2, NULL);
    thread_create(&thd[2], f3, NULL);
    thread_yield();

    for(i = 0; i < 3; i++)
	    thread_join(&thd[i], NULL);

	printf("END: Time stamp: %ld\n", get_timer());
}