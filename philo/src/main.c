/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:56:01 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/20 21:31:15 by tfilipe-         ###   ########.fr       */
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

void	*philo_routine(void *a)
{
	t_philo *philo = (t_philo *)a;
	pthread_mutex_lock(philo->left_fork);
	printf("OLA from %d\n", philo->id);
	pthread_mutex_unlock(philo->left_fork);

}

int 	start_philo(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]) != 0)
			return (printf("%s", ERR_THREAD_CREATE_FAIL), FAILURE);
		i++;
	}
		i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (printf("%s", ERR_THREAD_JOIN_FAIL), FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == FAILURE)
		return (FAILURE);
	if (init_all(&data, argc, argv) == FAILURE)
		return (FAILURE);
	start_philo(&data);
	// data.start_time = get_time();
	// usleep(5000);
	// long test = get_time();
	// printf("Current time: %ld ms\n", test - data.start_time );
	return (SUCCESS);
}
