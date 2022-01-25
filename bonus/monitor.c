/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonitor <gmonitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:40:36 by gmonitor          #+#    #+#             */
/*   Updated: 2022/01/25 19:42:35 by gmonitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitor_time(void *philo_raw)
{
	t_philo		*philo;
	int			count;
	int			finished_philos;
	long int	diff;

	philo = (t_philo *)philo_raw;
	count = 0;
	finished_philos = 0;
	sem_post(philo->rules->start);
	while (1)
	{
		diff = get_usec() - philo->death_time_count;
		if (diff > philo->rules->death_time)
		{
			sem_wait(philo->rules->somebody_dead);
			printf("%ld %d died\n", get_usec() \
				- philo->rules->starting_time, philo->id);
			sem_post(philo->rules->stop);
			return (NULL);
		}
	}
	return (NULL);
}

void	*monitor_eating(void *rules_raw)
{
	t_rules	*rules;
	int		count;

	count = 0;
	rules = (t_rules *)rules_raw;
	while (count < rules->philo_num)
	{
		sem_wait(rules->eat_enough);
		count++;
	}
	sem_post(rules->stop);
	return (NULL);
}
