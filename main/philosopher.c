/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonitor <gmonitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:56:00 by gmonitor          #+#    #+#             */
/*   Updated: 2022/01/25 19:30:54 by gmonitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	monitor_loop(t_rules *rules, int *finished_philos)
{
	int				count;
	long long int	diff;

	count = 0;
	while (count < rules->philo_num)
	{
		if (rules->philos[count].finish_meals != 1)
		{
			diff = get_usec(rules) - rules->philos[count].death_time_count;
			if (diff > rules->death_time)
			{
				print_message(rules, &rules->philos[count], DEAD);
				rules->finish_session = 1;
				return (1);
			}
		}
		else
			*finished_philos += 1;
		count++;
	}
	return (0);
}

void	*monitor_philo(void *rules_raw)
{
	t_rules			*rules;
	int				count;
	int				finished_philos;
	long long int	diff;

	rules = (t_rules *)rules_raw;
	count = 0;
	finished_philos = 0;
	pthread_mutex_lock(&rules->start);
	pthread_mutex_unlock(&rules->start);
	while (finished_philos != rules->philo_num)
		if (monitor_loop(rules, &finished_philos) == 1)
			return (NULL);
	return (NULL);
}

void	*philosopher(void *rules_raw)
{
	t_rules	*rules;
	t_philo	*philo;

	rules = (t_rules *)rules_raw;
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
			return (0);
		sleeping(rules, philo);
		thinking(rules, philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int				count;
	t_rules			rules;
	struct timeval	tv;
	time_t			res;
	t_philo			philo;

	if (argc < 5)
	{
		ft_check_args();
		return (1);
	}
	init_rules(&rules, argv, argc);
	init_mutex(&rules);
	init_philos(&rules);
	pthread_mutex_lock(&rules.start);
	init_pthread(&rules);
	pthread_mutex_unlock(&rules.start);
	destroy_pthread(&rules);
	destroy_mutex(&rules);
	destroy_malloc(&rules);
	return (0);
}
