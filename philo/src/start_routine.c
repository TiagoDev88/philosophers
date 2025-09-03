/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:46:08 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/09/03 12:14:47 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void my_sleep(long time_to)
{
    long start_time;
    long current_time;

    start_time = get_time();
    while (1)
    {
        usleep(100);
        current_time = get_time();
        if ((current_time - start_time) >= time_to)
            break;
    }
}


static void ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->data->mutex_meal);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->mutex_meal);
	print_message(philo, "is eating");
	my_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void ft_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	my_sleep(philo->data->time_to_sleep);
}

void ft_think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

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

static void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;
	int j;

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
			if (get_time() - data->philos[i].last_meal > data->time_to_die)
			{
				pthread_mutex_unlock(&data->mutex_meal);
				pthread_mutex_lock(&data->mutex_end_routine);
				pthread_mutex_lock(&data->mutex_print);
				data->end_routine = true;
				printf("%ld %d %s\n", (get_time() - data->start_routine), data->philos[i].id, "died");
				pthread_mutex_unlock(&data->mutex_print);
				pthread_mutex_unlock(&data->mutex_end_routine);
				return (NULL);
			}
			pthread_mutex_unlock(&data->mutex_meal);
			i++;
		}
		i = 0;
		j = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->mutex_meal);
			if (data->must_eat == data->philos[i].meals_eaten)
			{
				j++;
				if (j == data->num_philos)
				{
					pthread_mutex_lock(&data->mutex_end_routine);
					pthread_mutex_lock(&data->mutex_print);
					data->end_routine = true;
					printf("%ld %s\n", (get_time() - data->start_routine), "COMERAM TODOS!!!!!!!!!!");
					pthread_mutex_unlock(&data->mutex_print);
					pthread_mutex_unlock(&data->mutex_end_routine);
					pthread_mutex_unlock(&data->mutex_meal);
					return (NULL);
				}
			}
			pthread_mutex_unlock(&data->mutex_meal);
			i++;
		}
		usleep(500);
	}
	return NULL;
}

int 	start_dinner(t_data *data)
{
	int i;	

	i = 0;
	data->start_routine = get_time();
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
