# include "philosopher.h"

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
	return (res - rules->starting_time);
}

int	left(int n, int philo_num) { return (n - 1 + philo_num) % philo_num; }
int	right(int n, int philo_num) { return (n + 1) % philo_num; }

void    *monitor_philo(void *rules_raw)
{
	t_rules *rules = (t_rules *)rules_raw;
	int count;
	long long int diff;
	count = 0;
	pthread_mutex_lock(&rules->start);
	pthread_mutex_unlock(&rules->start);
	while (1)
	{
		while (count < rules->philo_num)
		{
			diff = get_usec(rules) - rules->philos[count]->death_time_count;
			if (diff > rules->death_time)
			{
				printf("%ld %d died\n", get_usec(rules), rules->philos[count]->id);
				rules->finish = 1;
				return NULL;
			}
			count++;
		}
		count = 0;
	}
}

void	*philosopher(void *rules_raw)
{
	t_rules *rules = (t_rules *)rules_raw;
	t_philo philo;
	long long int diff;
	long long int usec;

	init_philo(&philo, rules);
	rules->philos[philo.id] = &philo;

	pthread_mutex_lock(&rules->start);
	pthread_mutex_unlock(&rules->start);

	while (1)
	{
		pthread_mutex_lock(philo.first_f);
		if (rules->finish == 1)
			return 0;
		printf("%ld %d has taken a fork\n", get_usec(rules), philo.id);
		pthread_mutex_lock(philo.second_f);
		if (rules->finish == 1)
			return 0;
		printf("%ld %d has taken a fork\n", get_usec(rules), philo.id);

		if (rules->finish == 1)
			return 0;
		printf("%ld %d is eating\n", get_usec(rules), philo.id);
		ft_usleep(rules->eating_time);
		if (philo.meals_num >= 0)
		{
			if (philo.meals_num == 0)
			{
				pthread_mutex_unlock(philo.first_f);
				pthread_mutex_unlock(philo.second_f);
				return 0;
			}
			else
				philo.meals_num--;
		}

		philo.death_time_count = get_usec(rules);
		pthread_mutex_unlock(philo.first_f);
		pthread_mutex_unlock(philo.second_f);

		if (rules->finish == 1)
			return 0;
		printf("%ld %d is sleeping\n", get_usec(rules), philo.id);
		ft_usleep(rules->sleeping_time);
		if (rules->finish == 1)
			return 0;
		printf("%ld %d is thinking\n", get_usec(rules), philo.id);
	}
	return NULL;
}



int	main(int argc, char **argv)
{
	int				count;
	t_rules			rules;
	struct timeval	tv;
	time_t			res;
	gettimeofday(&tv, NULL);

	count = 0;
	if (argc < 2)
		return 0;
	init_rules(&rules, argv);
	init_mutex(&rules);

	pthread_mutex_lock(&rules.start);
	init_pthread(&rules);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;

	rules.starting_time = res;
	pthread_mutex_unlock(&rules.start);

	while (count < rules.philo_num)
		pthread_join(rules.threads[count++], NULL);
	count = 0;

	 while (count < rules.philo_num)
	 	pthread_mutex_destroy(&rules.forks[count++]);

	return 0;
}
