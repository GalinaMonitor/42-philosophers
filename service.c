# include "philosopher.h"

int	left(int n, int philo_num)
{
	return (n - 1 + philo_num) % philo_num;
}

int	right(int n, int philo_num)
{
	return (n + 1) % philo_num;
}

long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	ft_usleep(int ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 920);
	while (ft_time() < time + ms)
		usleep(ms * 3);
}

time_t	get_usec(t_rules *rules)
{
	struct	timeval tv;
	time_t	res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	print_message(t_rules *rules, t_philo *philo, int message)
{
	if (rules->finish_session == 1)
		return ;
	pthread_mutex_lock(&rules->lock_print);
	if (message == FORK)
		printf("%ld %d has taken a fork\n", get_usec(rules) - rules->starting_time, philo->id);
	else if (message == EAT)
		printf("%ld %d is eating\n", get_usec(rules) - rules->starting_time, philo->id);
	else if (message == SLEEP)
		printf("%ld %d is sleeping\n", get_usec(rules) - rules->starting_time, philo->id);
	else if (message == THINK)
		printf("%ld %d is thinking\n", get_usec(rules) - rules->starting_time, philo->id);
	else if (message == DEAD)
		printf("%ld %d died\n", get_usec(rules) - rules->starting_time, philo->id);
	pthread_mutex_unlock(&rules->lock_print);
}

