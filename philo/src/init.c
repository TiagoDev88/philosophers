/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:16:21 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/09/22 16:20:04 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	mutex_init(t_data *data)
{
	if (pthread_mutex_init(&data->mutex_end_routine, NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&data->mutex_meal, NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&data->mutex_print, NULL) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("%s", ERR_MUTEX_FAIL), FAILURE);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		data->philo[i].id = i;
		data->philo[i].last_meal = 0;
		data->philo[i].meals_eaten = 0;
		data->philo[i].left_fork = &data->forks[(i + 1) % data->num_philos];
		data->philo[i].right_fork = &data->forks[i];
		data->philo[i].data = data;
		i++;
	}
	if (mutex_init(data) != 0)
		return (printf("%s", ERR_MUTEX_FAIL), FAILURE);
	else
		return (SUCCESS);
}

int	init_all(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philo)
		return (printf("ERROR: Malloc t_philo failed\n"), FAILURE);
	data->forks = malloc(sizeof(t_mutex) * data->num_philos);
	if (!data->forks)
		return (printf("%s", ERR_MUTEX_MALLOC_FAIL), FAILURE);
	data->end_routine = false;
	if (init_philo(data) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
