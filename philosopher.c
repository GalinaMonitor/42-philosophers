# include "philosopher.h"


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

void	*philosopher(void *rules_raw)
{
	t_rules *rules = (t_rules *)rules_raw;
	t_philo philo;
	long long int diff;
	long long int usec;

	init_philo(&philo, rules);

	while (1)
	{
		pthread_mutex_lock(philo.first_f);
		printf("%ld %d has taken a fork\n", get_usec(rules), philo.id);
		pthread_mutex_lock(philo.second_f);
		printf("%ld %d has taken a fork\n", get_usec(rules), philo.id);

		printf("%ld %d is eating\n", get_usec(rules), philo.id);
		usleep(rules->eating_time * 1000);

		diff = get_usec(rules) - philo.death_time_count;
		philo.death_time_count = get_usec(rules);
		if (diff > rules->death_time)
		{
			printf("%ld %d died\n", get_usec(rules), philo.id);
			pthread_mutex_unlock(philo.first_f);
			pthread_mutex_unlock(philo.second_f);
			rules->finish = 1;
			return 0;
		}
		if (philo.nbr_meals >= 0)
		{
			if (philo.nbr_meals > 0)
				philo.nbr_meals--;
			else
			{
				pthread_mutex_unlock(philo.first_f);
				pthread_mutex_unlock(philo.second_f);
				return 0;
			}
		}
		if (rules->finish == 1)
			return 0;
		pthread_mutex_unlock(philo.first_f);
		pthread_mutex_unlock(philo.second_f);

		printf("%ld %d is sleeping\n", get_usec(rules), philo.id);
		usleep(rules->sleeping_time * 1000);
		printf("%ld %d is thinking\n", get_usec(rules), philo.id);
	}
	return NULL;
}



int	main(int argc, char **argv)
{
	int				count;
	t_rules			rules;

	count = 0;
	if (argc < 2)
		return 0;

	init_rules(&rules, argv);
	init_mutex(&rules);

	pthread_mutex_lock(&rules.start);
	init_pthread(&rules);
	pthread_mutex_unlock(&rules.start);

	while (count < rules.philo_num)
		pthread_join(rules.threads[count++], NULL);
	count = 0;

	while (count < rules.philo_num)
		pthread_mutex_destroy(&rules.forks[count++]);

	return 0;
}
