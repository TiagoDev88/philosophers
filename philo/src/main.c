/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:56:01 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/28 15:37:00 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("%s", ERR_ARGS), FAILURE);
	if (!only_num(argv))
		return (printf("%s", ERR_ONLY_NUM), FAILURE);
	return (SUCCESS);
}

//TODO tv_sec para segundos, e tv_usec para microssegundos
// tv_sec * 1000 para passar para milissegundos
// tv_usec / 1000 para passar para milissegundos
// somo os os dois valores para obter o tempo total em milissegundos
long get_time()
{
	long res;
	struct timeval time;

	res = 0;
	gettimeofday(&time, NULL);
	res += time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}

void	*philo_routine(void *arg)
{
	// printf("MEMORIA ARG %p\n", arg); // porque 16???? 
	t_philo *philo = (t_philo *)arg;
	while (1)
	{
		long soma_tmd = get_time() - philo->data->start_routine;
		// printf("soma %ld\n", soma_tmd);
		if (philo->last_meal > soma_tmd)
		{
			printf("passou o tempo do %d que e %ld e  atual %ld\n",philo->id,philo->last_meal, soma_tmd);
			break;
		}
		// if (philo->id % 2 == 0)
		// 	usleep(1000);
		pthread_mutex_lock(philo->left_fork);	
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", (get_time() - philo->data->start_routine), philo->id);
		printf("%ld %d has taken a fork\n", (get_time() - philo->data->start_routine), philo->id);

		philo->last_meal = (get_time() - philo->data->start_routine);
		printf("%ld %d is eating\n", (get_time() - philo->data->start_routine), philo->id);
		usleep(philo->data->time_to_eat * 1000);
		
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		pthread_mutex_lock(&philo->data->print_printf);
		printf("%ld %d is sleeping\n", (get_time() - philo->data->start_routine), philo->id);
		usleep(philo->data->time_to_sleep * 1000);
		pthread_mutex_unlock(&philo->data->print_printf);

		pthread_mutex_lock(&philo->data->print_printf);
		printf("%ld %d is thinking\n", (get_time() - philo->data->start_routine), philo->id);
		pthread_mutex_unlock(&philo->data->print_printf);

	}

	return (NULL);


}



int 	start_dinner(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &philo_routine, &data->philos[i]) != 0)
			return (printf("%s", ERR_THREAD_CREATE_FAIL), FAILURE);
		i++;
	}

	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;
	memset(&data, 0, sizeof(t_data));

	if (check_args(argc, argv) == FAILURE)
		return (FAILURE);
	if (init_all(&data, argc, argv) == FAILURE)
		return (FAILURE);


	data.start_routine = get_time();
	
	start_dinner(&data);
	
	int	i = 0;
	while (i < data.num_philos)
	{
		if (pthread_join(data.philos[i].thread_id, NULL) != 0)
			return (printf("%s", ERR_THREAD_JOIN_FAIL), FAILURE);
		i++;
	}
	
	// usleep(5000);
	// long test = get_time();
	// printf("Current time: %ld ms\n", test - data.start_time );
	return (SUCCESS);
}
