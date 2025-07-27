/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:56:01 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/07/27 17:49:22 by tfilipe-         ###   ########.fr       */
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
	t_philo *philo = (t_philo *)arg;
	printf("time to eat %ld\n", &philo->data->time_to_eat); // porque 16???? 
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	// pthread_mutex_lock(&philo->data->print_printf);
	printf("PICK right fork %p from philo %d\n", philo->right_fork, philo->id);
	printf("PICK left fork %p from philo %d\n", philo->left_fork, philo->id);
	printf("Philo %d is eating\n", philo->id);

	// pthread_mutex_unlock(&philo->data->print_printf);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	// printf("time to eat %ld\n", philo->data->time_to_eat);
	// usleep(philo->data->time_to_eat * 1000);
	printf("Philo %d is sleeping\n", philo->id);
	// usleep(philo->data->time_to_sleep * 1000);
	// printf("time to sleep %ld\n", philo->data->time_to_sleep);
	printf("Philo %d is thinking\n", philo->id);

	// pthread_mutex_lock(&philo->data->print_printf); 


	// //pthread_mutex_lock(&philo->data->print_printf);
	// //pthread_mutex_unlock(&philo->data->print_printf);

	// //pthread_mutex_lock(&philo->data->print_printf);
	// //pthread_mutex_unlock(&philo->data->print_printf);

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
		i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].thread_id, NULL) != 0)
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
	//data.start_routine = get_time();
	// printf("time to eat %ld\n", data.time_to_eat);

	start_dinner(&data);
	
	// data.start_time = get_time();
	// usleep(5000);
	// long test = get_time();
	// printf("Current time: %ld ms\n", test - data.start_time );
	return (SUCCESS);
}
