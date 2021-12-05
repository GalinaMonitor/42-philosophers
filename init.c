#include "philosopher.h"

void	init_philo(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->set_id);
	philo->id = rules->philo_id;
	rules->philo_id++;
	pthread_mutex_unlock(&rules->set_id);

	if (philo->id % 2 == 0 && philo->id == rules->philo_num)
	{
		philo->first_f = &(rules->forks[philo->id]);
		philo->second_f = &(rules->forks[right(philo->id, rules->philo_num)]);
	}
	else
	{
		philo->first_f = &rules->forks[right(philo->id, rules->philo_num)];
		philo->second_f = &rules->forks[philo->id];
	}

	philo->death_time_count = 0;
	philo->nbr_meals = rules->nbr_meals;

	philo->left_ph = left(philo->id, rules->philo_num);
	philo->right_ph = right(philo->id, rules->philo_num);
}

void	init_rules(t_rules *rules, char **argv)
{
	struct timeval	tv;
	time_t			res;
	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;

	rules->philo_num = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->eating_time = ft_atoi(argv[3]);
	rules->sleeping_time = ft_atoi(argv[4]);
	// if (argv[5] != NULL)
	// 	rules->nbr_meals = ft_atoi(argv[5]);
	// else
	// 	rules->nbr_meals = -1;
	rules->starting_time = res;
	rules->philo_id = 0;
	rules->finish = 0;
}

void	init_mutex(t_rules *rules)
{
	int count;
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t) * rules->philo_num);
	count = 0;
	while (count < rules->philo_num)
		pthread_mutex_init(&(mutex[count++]), NULL);
	pthread_mutex_init(&rules->set_id, NULL);
	pthread_mutex_init(&rules->start, NULL);
	rules->forks = mutex;
}

void	init_pthread(t_rules *rules)
{
	int			count;
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_mutex_t) * rules->philo_num);

	count = 0;
	while (count < rules->philo_num)
	{
		pthread_create(&threads[count], NULL, philosopher, rules);
		count++;
	}
	rules->threads = threads;
}
