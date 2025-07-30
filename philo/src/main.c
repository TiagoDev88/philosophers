/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:56:01 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/30 13:20:40 by tfilipe-         ###   ########.fr       */
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

void print_message(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->mutex_end_routine);
	pthread_mutex_lock(&philo->data->mutex_print);
	if (philo->data->end_routine == false)
		printf("%ld %d %s\n", get_time() - philo->data->start_routine, philo->id, message);
	pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_unlock(&philo->data->mutex_end_routine);
}


void	*philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_start);
		if (philo->data->started == true)
		{
			pthread_mutex_unlock(&philo->data->mutex_start);
			break;
		}
		pthread_mutex_unlock(&philo->data->mutex_start);
		usleep(50);
	}
	pthread_mutex_lock(&philo->data->mutex_print);
	philo->last_meal = philo->data->start_routine;
	pthread_mutex_unlock(&philo->data->mutex_print);
	while (1)
	{		

		pthread_mutex_lock(&philo->data->mutex_end_routine);
		if (philo->data->end_routine == true)
		{
			pthread_mutex_unlock(&philo->data->mutex_end_routine);
			break;
		}
		pthread_mutex_unlock(&philo->data->mutex_end_routine);

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
		usleep(philo->data->time_to_eat * 1000);
		
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		
		print_message(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);

		print_message(philo, "is thinking");
	}
	return (NULL);
}

void *monitor_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int i;
	while (1)
	{
		pthread_mutex_lock(&data->mutex_start);
		if (data->started == true)
		{
			pthread_mutex_unlock(&data->mutex_start);
			break;
		}
		pthread_mutex_unlock(&data->mutex_start);
		usleep(50);
	}
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

				return NULL;
			}
			pthread_mutex_unlock(&data->mutex_meal);
			i++;
		}
		usleep(1000);
	}
	return NULL;
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

	if (pthread_create(&data->monitor, NULL, &monitor_routine, data) != 0)
			return (printf("%s", ERR_THREAD_CREATE_FAIL), FAILURE);

	pthread_mutex_lock(&data->mutex_start);
	pthread_mutex_lock(&data->mutex_print);
	data->started = true;
	data->start_routine = get_time();
	pthread_mutex_unlock(&data->mutex_print);
	pthread_mutex_unlock(&data->mutex_start);
	return (SUCCESS);
}


int free_all(t_data *data)
{
	int i;

	if (pthread_join(data->monitor, NULL) != 0)
			return (printf("%s", ERR_THREAD_JOIN_FAIL), FAILURE);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
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
	free(data->philos);
	pthread_mutex_destroy(&data->mutex_end_routine);
	pthread_mutex_destroy(&data->mutex_meal);
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_start);

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
