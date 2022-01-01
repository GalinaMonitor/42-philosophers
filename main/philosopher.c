# include "philosopher.h"

void	*monitor_philo(void *rules_raw)
{
	t_rules *rules;
	int count;
	int finished_philos;
	long long int diff;

	rules = (t_rules *)rules_raw;
	count = 0;
	finished_philos = 0;
	pthread_mutex_lock(&rules->start);
	pthread_mutex_unlock(&rules->start);
	while (finished_philos != rules->philo_num)
	{
		while (count < rules->philo_num)
		{
			if (rules->philos[count].finish_meals != 1)
			{
				diff = get_usec(rules) - rules->philos[count].death_time_count;
				if (diff > rules->death_time)
				{
					print_message(rules, &rules->philos[count], DEAD);
					rules->finish_session = 1;
					return NULL;
				}
			}
			else
				finished_philos += 1;
			count++;
		}
		count = 0;
	}
	return NULL;
}

void	*philosopher(void *rules_raw)
{
	t_rules *rules = (t_rules *)rules_raw;
	t_philo *philo;

	pthread_mutex_lock(&rules->set_id);
	rules->philo_id--;
	philo = &rules->philos[rules->philo_id];
	pthread_mutex_unlock(&rules->set_id);
	pthread_mutex_lock(&rules->start);
	pthread_mutex_unlock(&rules->start);
	while (1)
	{
		eating(rules, philo);
		if (rules->finish_session || philo->finish_meals)
			return 0;
		sleeping(rules, philo);
		thinking(rules, philo);
	}
	return NULL;
}



int	main(int argc, char **argv)
{
	int				count;
	t_rules			rules;
	struct timeval	tv;
	time_t			res;
	t_philo philo;

	init_rules(&rules, argv, argc);
	init_mutex(&rules);
	init_philos(&rules);
	pthread_mutex_lock(&rules.start);
	init_pthread(&rules);
	pthread_mutex_unlock(&rules.start);
	destroy_pthread(&rules);
	destroy_mutex(&rules);
	return 0;
}
