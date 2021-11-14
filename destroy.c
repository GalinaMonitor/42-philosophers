#include "philosopher.h"

void	destroy_mutex(t_rules *rules)
{
	int count;

	count = 0;
	while (count < rules->philo_num)
		pthread_mutex_unlock(&(rules->forks[count++]));
	count = 0;
	while (count < rules->philo_num)
		pthread_mutex_destroy(&(rules->forks[count++]));
	pthread_mutex_destroy(&rules->set_id);
	pthread_mutex_destroy(&rules->start);
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
}
