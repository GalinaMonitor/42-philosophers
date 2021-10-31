# include "philosopher.h"


long int	get_usec()
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return(current_time.tv_usec);
}



int	left(int n, int philo_num) { return (n - 1 + philo_num) % philo_num; }
int	right(int n, int philo_num) { return (n + 1) % philo_num; }



void	*philosopher(void *rules_raw)
{
	t_rules *rules = (t_rules *)rules_raw;
	t_philo philo;
	long int diff;
	long int usec;

	init_philo(&philo, rules);

	printf("%d\n", philo.id);
	philo.death_time_count = get_usec();
	while (1)
	{
		printf("%ld %d is thinking\n", get_usec(), philo.id);
		pthread_mutex_lock(philo.left_f);
		printf("%ld %d has taken a fork\n", get_usec(), philo.id);
		pthread_mutex_lock(philo.right_f);
		printf("%ld %d has taken a fork\n", get_usec(), philo.id);

		diff = get_usec() - philo.death_time_count;
		if (diff < 0)
			diff = 1000000 + diff;
		if (diff > rules->death_time * 1000)
		{
			printf("%ld %d died\n", get_usec(), philo.id);
			return 0;
		}

		printf("%ld %d is eating\n", get_usec(), philo.id);
		usleep(rules->eating_time * 1000);
		philo.death_time_count = get_usec();
		pthread_mutex_unlock(philo.left_f);
		pthread_mutex_unlock(philo.right_f);
		printf("%ld %d is sleeping\n", get_usec(), philo.id);
		usleep(rules->sleeping_time * 1000);
	}
	return NULL;
}



int	main(int argc, char **argv)
{
	int				count;
	pthread_t		threads[ft_atoi(argv[1])];
	pthread_mutex_t	mutex[ft_atoi(argv[1])];
	t_rules			rules;

	count = 0;
	if (argc < 2)
		return 0;

	init_rules(&rules, argv);
	init_mutex(&rules, mutex);
	rules.forks = mutex;

	pthread_mutex_lock(&rules.start);
	init_pthread(&rules, threads);
	pthread_mutex_unlock(&rules.start);

	while (count < rules.philo_num)
		pthread_join(threads[count++], NULL);
	count = 0;

	while (count < rules.philo_num)
		pthread_mutex_destroy(&mutex[count++]);

	return 0;
}
