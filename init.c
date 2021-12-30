#include "philosopher.h"

void	init_philo(t_philo *philo, t_rules *rules)
{
	philo->id = rules->philo_id;
	rules->philo_id++;
	philo->meals_num = rules->meals_num;
	if (philo->id % 2 == 1)
	{
		philo->first_f = &(rules->forks[philo->id]);
		philo->second_f = &(rules->forks[right(philo->id, rules->philo_num)]);
	}
	else
	{
		philo->first_f = &rules->forks[right(philo->id, rules->philo_num)];
		philo->second_f = &rules->forks[philo->id];
	}
	philo->death_time_count = rules->starting_time;
	philo->finish_meals = 0;
	philo->left_ph = left(philo->id, rules->philo_num);
	philo->right_ph = right(philo->id, rules->philo_num);
}

void	init_rules(t_rules *rules, char **argv, int argc)
{
	if (argc < 2)
		return ;

	rules->philo_num = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->eating_time = ft_atoi(argv[3]);
	rules->sleeping_time = ft_atoi(argv[4]);
	rules->starting_time = get_usec(rules);
	if (argv[5] != NULL)
		rules->meals_num = ft_atoi(argv[5]);
	else
		rules->meals_num = -1;
	rules->philo_id = 0;
	rules->finish_session = 0;
	rules->philos = malloc(sizeof(t_philo) * rules->philo_num);
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
	pthread_mutex_init(&rules->lock_print, NULL);
	rules->forks = mutex;
}

void	init_pthread(t_rules *rules)
{
	int			count;
	pthread_t	*threads;
	pthread_t	*monitor;

	threads = malloc(sizeof(pthread_mutex_t) * rules->philo_num);
	count = 0;
	while (count < rules->philo_num)
		pthread_create(&threads[count++], NULL, philosopher, rules);
	monitor = malloc(sizeof(pthread_mutex_t));
	pthread_create(monitor, NULL, monitor_philo, rules);
	rules->monitor = monitor;
	rules->threads = threads;
}

void	init_philos(t_rules *rules)
{
	int count;

	count = 0;
	while (count < rules->philo_num)
		init_philo(&rules->philos[count++], rules);
}
