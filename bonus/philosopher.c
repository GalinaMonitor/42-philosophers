/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonitor <gmonitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:40:39 by gmonitor          #+#    #+#             */
/*   Updated: 2022/01/25 18:46:32 by gmonitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_kill_philosophers(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_num)
	{
		kill(rules->pid_philos[i], SIGKILL);
		i++;
	}
}

void	*philosopher(t_rules *rules, t_philo *philo)
{
	pthread_create(&rules->monitors_time[philo->id], NULL, monitor_time, philo);
	pthread_detach(rules->monitors_time[philo->id]);
	sem_wait(rules->start);
	sem_post(rules->start);
	while (1)
	{
		eating(rules, philo);
		if (philo->finish_meals == 1)
		{
			sem_post(philo->rules->eat_enough);
			exit(0);
		}
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
	init_sem(&rules);
	init_philos(&rules);
	sem_wait(rules.stop);
	ft_kill_philosophers(&rules);
	destroy_malloc(&rules);
	return (0);
}
