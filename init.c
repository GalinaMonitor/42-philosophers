#include "philosopher.h"

void	init_philo(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->set_id);
	philo->id = rules->philo_id;
	rules->philo_id++;
	pthread_mutex_unlock(&rules->set_id);

	philo->death_time_count = 0;

	philo->left_f = &rules->forks[philo->id];
	philo->right_f = &rules->forks[right(philo->id, rules->philo_num)];

	philo->left_ph = left(philo->id, rules->philo_num);
	philo->right_ph = right(philo->id, rules->philo_num);
}

void	init_rules(t_rules *rules, char **argv)
{
	rules->philo_num = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->eating_time = ft_atoi(argv[3]);
	rules->sleeping_time = ft_atoi(argv[4]);
	rules->philo_id = 0;
}

void	init_mutex(t_rules *rules, pthread_mutex_t *mutex)
{
	int count;

	count = 0;
	while (count < rules->philo_num)
		pthread_mutex_init(&(mutex[count++]), NULL);
	pthread_mutex_init(&rules->set_id, NULL);
	pthread_mutex_init(&rules->start, NULL);
}

void	init_pthread(t_rules *rules, pthread_t *threads)
{
	int count;

	count = 0;
	while (count < rules->philo_num)
	{
		pthread_create(&threads[count], NULL, philosopher, rules);
		count++;
	}
}
