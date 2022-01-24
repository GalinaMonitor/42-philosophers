# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
# include "../libft/libft/libft.h"

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4

typedef struct		s_philo
{
	int				id;
	int				left_ph;
	int				right_ph;
	int				meals_num;

	long int		death_time_count;
	int				finish_meals;
}					t_philo;

typedef struct		s_rules
{
	int				philo_id;

	int				philo_num;
	long long int	eating_time;
	long long int	death_time;
	long long int	sleeping_time;
	time_t			starting_time;
	int				finish_session;
	int				meals_num;

	t_philo			*philos;

	pid_t			*pid_philos;
	sem_t			*write_sem;
	sem_t			*fork_sem;
	sem_t			*stop;
	sem_t			*eat_enough;
	pthread_t		*monitor;
}					t_rules;


int			init_philo(t_philo *philo, t_rules *rules);
void			init_rules(t_rules *rules, char **argv, int argc);
void			init_pthread(t_rules *rules);
void			init_sem(t_rules *rules);

void	destroy_mutex(t_rules *rules);

void	destroy_pthread(t_rules *rules);

time_t	get_usec(t_rules *rules);

int				left(int n, int philo_num);
int				right(int n, int philo_num);

void			*philosopher(t_rules *rules, t_philo *philo);

void			*monitor_philo(void *rules_raw);

void	print_message(t_rules *rules, t_philo *philo, int message);
void	sleeping(t_rules *rules, t_philo *philo);
void	eating(t_rules *rules, t_philo *philo);
void	thinking(t_rules *rules, t_philo *philo);

void	ft_usleep(int ms);

long	ft_time(void);

void	ft_usleep(int ms);
int	left(int n, int philo_num);
int	right(int n, int philo_num);

void	destroy_malloc(t_rules *rules);

void	init_philos(t_rules *rules);
