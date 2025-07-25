#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

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
	struct s_fork	*left_fork;
	struct s_fork	*right_fork;
	pthread_t		thread_id;
	struct s_data	*data;
}				t_philo;

typedef struct s_fork
{
	t_mtx			*forks; 
	int				fork_id; 
}					t_fork;

typedef struct s_data
{
	long			num_philos; 
	long			time_to_die; 
	long			time_to_eat; 
	long			time_to_sleep; 
	long			must_eat;
	long			start_routine; 
	bool			end_routine;
	t_philo			*philos;
	t_fork			*forks;
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