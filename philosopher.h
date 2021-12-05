# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include "libft/libft/libft.h"

typedef struct		s_philo
{
	int				id;
	int				left_ph;
	int				right_ph;
	int				nbr_meals;

	pthread_mutex_t	*first_f;
	pthread_mutex_t	*second_f;

	long int 		death_time_count;
}					t_philo;

typedef struct		s_rules
{
	int				philo_id;

	int				philo_num;
	int				nbr_meals;
	long long int	eating_time;
	long long int	death_time;
	long long int	sleeping_time;
	time_t			starting_time;
	int				finish;

	t_philo         *philos;

	pthread_mutex_t set_id;
	pthread_mutex_t start;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_t		*monitor;
}					t_rules;


void			init_philo(t_philo *philo, t_rules *rules);
void			init_rules(t_rules *rules, char **argv);
void			init_pthread(t_rules *rules);
void			init_mutex(t_rules *rules);

void	destroy_mutex(t_rules *rules);

void	destroy_pthread(t_rules *rules);

long int		get_usec();

int				left(int n, int philo_num);
int				right(int n, int philo_num);

void			*philosopher(void *rules_raw);

void			*monitor_philo(void *rules_raw);