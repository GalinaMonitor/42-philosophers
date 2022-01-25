/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonitor <gmonitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:40:23 by gmonitor          #+#    #+#             */
/*   Updated: 2022/01/25 19:35:24 by gmonitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eating(t_rules *rules, t_philo *philo)
{
	sem_wait(rules->fork_sem);
	print_message(rules, philo, FORK);
	sem_wait(rules->fork_sem);
	print_message(rules, philo, FORK);
	print_message(rules, philo, EAT);
	philo->death_time_count = get_usec();
	ft_usleep(rules->eating_time);
	if (philo->meals_num >= 0)
		philo->meals_num--;
	if (philo->meals_num == 0)
		philo->finish_meals = 1;
	sem_post(rules->fork_sem);
	sem_post(rules->fork_sem);
}

void	sleeping(t_rules *rules, t_philo *philo)
{
	print_message(rules, philo, SLEEP);
	ft_usleep(rules->sleeping_time);
}

void	thinking(t_rules *rules, t_philo *philo)
{
	print_message(rules, philo, THINK);
}
