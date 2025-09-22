/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_start_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:11:34 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/09/22 16:16:27 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	my_sleep(long time_to)
{
	long	start_time;
	long	current_time;

	start_time = get_time();
	while (1)
	{
		usleep(100);
		current_time = get_time();
		if ((current_time - start_time) >= time_to)
			break ;
	}
}

void	ft_eat(t_philo *philo)
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

void	ft_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	my_sleep(philo->data->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	print_message(philo, "is thinking");
	my_sleep(1);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_unlock(philo->left_fork);
}
