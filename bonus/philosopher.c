# include "philosopher.h"


static void	ft_kill_philosophers(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		kill(rules->pid_philos[i], SIGKILL);
		i++;
	}
}


void	*monitor_philo(void *rules_raw)
{
	t_rules *rules;
	int count;
	int finished_philos;
	long int diff;

	rules = (t_rules *)rules_raw;
	count = 0;
	finished_philos = 0;
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
					ft_kill_philosophers(rules);
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

void	*philosopher(t_rules *rules, t_philo *philo)
{
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
	init_sem(&rules);
	init_philos(&rules);
	ft_usleep(2000);
	ft_kill_philosophers(&rules);
	return 0;
}
