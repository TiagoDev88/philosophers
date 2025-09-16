/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:46:08 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/09/16 18:37:46 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	pthread_mutex_lock(&philo->data->mutex_meal);
	philo->last_meal = philo->data->start_routine;
	pthread_mutex_unlock(&philo->data->mutex_meal);
	if (philo->data->num_philos == 1)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_end_routine);
		if (philo->data->end_routine == true)
		{
			pthread_mutex_unlock(&philo->data->mutex_end_routine);
			break;
		}
		pthread_mutex_unlock(&philo->data->mutex_end_routine);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

// static int monitor_check_died(t_data *data)
// {
	
// }

static int monitor_meals_count(t_data *data)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->mutex_meal);
		if (data->must_eat == data->philos[i].meals_eaten)
			count++;
		pthread_mutex_unlock(&data->mutex_meal);
		i++;
	}
	if (count == data->must_eat)
	{
		pthread_mutex_lock(&data->mutex_end_routine);
		pthread_mutex_lock(&data->mutex_print);
		data->end_routine = true;
		printf("%ld %s\n", (ft_get_time() - data->start_routine), "COMERAM TODOS!!!!!!!!!!");
		pthread_mutex_unlock(&data->mutex_print);
		pthread_mutex_unlock(&data->mutex_end_routine);
		pthread_mutex_unlock(&data->mutex_meal);
		return (SUCCESS);
	}
	return (FAILURE);
}

static void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;

	while (1)
	{
		pthread_mutex_lock(&data->mutex_end_routine);
		if (data->end_routine == true)
		{
			pthread_mutex_unlock(&data->mutex_end_routine);
			break;
		}
		pthread_mutex_unlock(&data->mutex_end_routine);
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->mutex_meal);
			if (ft_get_time() - data->philos[i].last_meal > data->time_to_die)
			{
				pthread_mutex_unlock(&data->mutex_meal);
				pthread_mutex_lock(&data->mutex_end_routine);
				pthread_mutex_lock(&data->mutex_print);
				data->end_routine = true;
				printf("%ld %d %s\n", (ft_get_time() - data->start_routine), data->philos[i].id, "died");
				pthread_mutex_unlock(&data->mutex_print);
				pthread_mutex_unlock(&data->mutex_end_routine);
				return (NULL);
			}
			pthread_mutex_unlock(&data->mutex_meal);
			i++;
		}
		// count da comida
		if (monitor_meals_count(data) == SUCCESS)
			return (NULL);
		usleep(500);
	}
	return NULL;
}

int	start_dinner(t_data *data)
{
	int i;	

	i = 0;
	data->start_routine = ft_get_time();
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread_id, NULL, &philo_routine, &data->philos[i]) != 0)
			return (printf("%s", ERR_THREAD_CREATE_FAIL), FAILURE);
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &monitor_routine, data) != 0)
			return (printf("%s", ERR_THREAD_CREATE_FAIL), FAILURE);
	return (SUCCESS);
}
