#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>


typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long			start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}				t_data;

int		ft_atoi(const char *str);

#endif