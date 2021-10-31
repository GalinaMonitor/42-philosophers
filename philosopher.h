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

	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;

	long int 		death_time_count;
}					t_philo;

typedef struct		s_rules
{
	int				philo_id;

	int				philo_num;
	int				eating_time;
	long int		death_time;
	int				sleeping_time;

	pthread_mutex_t set_id;
	pthread_mutex_t start;
	pthread_mutex_t	*forks;
}					t_rules;


void			init_philo(t_philo *philo, t_rules *rules);
void			init_rules(t_rules *rules, char **argv);
void			init_pthread(t_rules *rules, pthread_t *threads);
void			init_mutex(t_rules *rules, pthread_mutex_t *mutex);

long int		get_usec();

int				left(int n, int philo_num);
int				right(int n, int philo_num);

void			*philosopher(void *rules_raw);
