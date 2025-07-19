#include "../includes/philo.h"



//TODO criar multiplos threads (FILOSOFOS)
int main(int argc, char** argv)
{
    int philo = ft_atoi(argv[1]);
    pthread_t th[philo];
    for (int i = 0; i < philo; i++)
        printf("Nr philos: %d\n", i);
    return 0;
}
