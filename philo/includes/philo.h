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
# define ERR_MUTEX_FAIL "ERROR: Mutex Failed\n"
# define ERR_MUTEX_MALLOC_FAIL "ERROR: Malloc Mutex Failed\n"
# define ERR_THREAD_CREATE_FAIL "ERROR: Failed to create thread for philosopher\n"
# define ERR_THREAD_JOIN_FAIL "Failed to join thread for philosopher\n"

typedef pthread_mutex_t		t_mtx;

typedef enum e_code
{
	SUCCESS,
	FAILURE
}			t_code;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				meals_eaten;
	t_mtx			*left_fork;
	t_mtx			*right_fork;
	pthread_t		thread;
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
	t_mtx			*forks;
	t_mtx			print_printf;
} t_data;

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