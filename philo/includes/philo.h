#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

# define ERR_ONLY_NUM "ERROR: Only numbers from 1 to INT_MAX allowed\n"
# define ERR_ARGS "ERROR: Usage: ./philo <num_philos> <time_to_die> \
<time_to_eat> <time_to_sleep> OPTIONAL-> [<must_eat>]\n"



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

/* utils.c */
int		ft_atoi(const char *str);
int		ft_atol(char *s);
int		only_num(char **argv);
/* init.c */
int		init_philo(t_data *data);
int		init_all(t_data *data, int argc, char **argv);
/* main.c */
int		check_args(int argc, char **argv);

#endif