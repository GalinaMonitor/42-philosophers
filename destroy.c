#include "philosopher.h"

void	destroy_mutex(t_rules *rules)
{
	int count;

	count = 0;
	while (count < rules->philo_num)
		pthread_mutex_destroy(&(rules->forks[count++]));
	pthread_mutex_destroy(&rules->set_id);
	pthread_mutex_destroy(&rules->start);
	pthread_mutex_destroy(&rules->lock_print);
}

void	destroy_pthread(t_rules *rules)
{
	int			count;

	count = 0;
	while (count < rules->philo_num)
	{
		pthread_join(rules->threads[count], NULL);
		count++;
	}
	pthread_join(*rules->monitor, NULL);
}

void	destroy_malloc(t_rules *rules)
{
	int count;

	count = 0;
	while (count < rules->philo_num)
		free(&rules->threads[count++]);
}
