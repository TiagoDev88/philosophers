
#include "../includes/philo.h"

int x = 2;
int mails = 0;
int lock = 0;
pthread_mutex_t	mutex;

//TODO podemos ter multiplos threads no mesmo processo
void*	routine()
{
	printf("Test from threads\n");
	printf("Process id %d\n", getpid());
	x++;
	sleep(3);
	printf("Value of x: %d\n", x);
	printf("Ending thread\n");
	printf("Process id %d\n", getpid());

}
//TODO as variaveis sao acedidas ao mesmo tempo na mesma memoria, diferente do fork nos processos que faz uma copia
// aqui elas sao acedidas a mesma variavel.
void*	routine2()
{
	printf("Test from threads\n");
	printf("Process id %d\n", getpid());
	sleep(3);
	printf("Value of x: %d\n", x);
	printf("Ending thread\n");
	printf("Process id %d\n", getpid());

}
//TODO como funciona a race condition, commo nao tem, ele t2 fica parado no 23, e quando for a incrementar fica 24
// com 10000 ele da certo mas se usar 100000, ja da mal o valor || compilar com -S para ir ao assembly
// entao usamos o pthread_mutex
//vai entrar com o valor 23
//		t1	|	t2
//read	30	|	23
//incr	30	|	30
//writ	31	|	24

void *race_condition()
{
	for (int i = 0; i < 10000; i++)
		mails++;
}

//TODO aqui vou usar o pthread mutex para dar LOCK e UNLOCK
// e assim as threads esperam uma pela outra.
//		t1	|	t2
//read	30	|	23
//incr	30	|	30
//writ	31	|	24
void *race_condition1()
{
	for (int i = 0; i < 10000000; i++)
	{
		//esperar que o lock fique 0
		pthread_mutex_lock(&mutex); // como se fosse lock = 1
		mails++;
		pthread_mutex_unlock(&mutex); // como se fosse o lock = 0
	}
}

//TODO MAIN THREADS: estas funcoes convem verificar se retorna erro. Se for diferente de 0.
// se for 0 foi criado com sucesso.
int	main(int argc, char **argv)
{
	pthread_t t1, t2;
	//vou usar para iniciar o mutex, porque preciso de iniciar o mutex.
	//e depois no fim tenho que o destruir.
	pthread_mutex_init(&mutex, NULL);
	// if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	// 	return 1;
	// if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
	// 	return 2;
	if (pthread_create(&t1, NULL, &race_condition1, NULL) != 0)
		return 1;
	if (pthread_create(&t2, NULL, &race_condition1, NULL) != 0)
		return 2;
	if (pthread_join(t1, NULL) != 0)
		return 3;
	if (pthread_join(t2, NULL) != 0)
		return 4;
	printf("Emails: %d\n", mails);
	//aqui esta para destruir o mutex (GARFO/ FORK)
	pthread_mutex_destroy(&mutex);
	return (0);
}

