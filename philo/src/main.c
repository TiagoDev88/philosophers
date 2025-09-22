/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:56:01 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/09/22 16:18:01 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (printf("%s", ERR_ARGS), FAILURE);
	if (!only_num(argv))
		return (printf("%s", ERR_ONLY_NUM), FAILURE);
	return (SUCCESS);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_message(t_philo *ph, const char *msg)
{
	pthread_mutex_lock(&ph->data->mutex_end_routine);
	pthread_mutex_lock(&ph->data->mutex_print);
	if (ph->data->end_routine == false)
		printf("%ld %d %s\n", get_time() - ph->data->start_routine,
			ph->id + 1, msg);
	pthread_mutex_unlock(&ph->data->mutex_print);
	pthread_mutex_unlock(&ph->data->mutex_end_routine);
}

int	free_all(t_data *data)
{
	int	i;

	if (pthread_join(data->monitor, NULL) != 0)
		return (printf("%s", ERR_THREAD_JOIN_FAIL), FAILURE);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philo[i].thread_id, NULL) != 0)
			return (printf("%s", ERR_THREAD_JOIN_FAIL), FAILURE);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	free(data->philo);
	pthread_mutex_destroy(&data->mutex_end_routine);
	pthread_mutex_destroy(&data->mutex_meal);
	pthread_mutex_destroy(&data->mutex_print);
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
	if (start_dinner(&data) == FAILURE)
	{
		free_all(&data);
		return (FAILURE);
	}
	free_all(&data);
	return (SUCCESS);
}
