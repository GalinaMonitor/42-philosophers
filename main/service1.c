/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonitor <gmonitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:49:35 by gmonitor          #+#    #+#             */
/*   Updated: 2022/01/25 18:52:39 by gmonitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(int ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 920);
	while (ft_time() < time + ms)
		usleep(ms * 3);
}

time_t	get_usec(t_rules *rules)
{
	struct timeval	tv;
	time_t			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	print_message(t_rules *rules, t_philo *philo, int message)
{
	if (rules->finish_session == 1)
		return ;
	pthread_mutex_lock(&rules->lock_print);
	if (message == FORK)
		printf("%ld %d has taken a fork\n", get_usec(rules) \
			- rules->starting_time, philo->id);
	else if (message == EAT)
		printf("%ld %d is eating\n", get_usec(rules) \
			- rules->starting_time, philo->id);
	else if (message == SLEEP)
		printf("%ld %d is sleeping\n", get_usec(rules) \
			- rules->starting_time, philo->id);
	else if (message == THINK)
		printf("%ld %d is thinking\n", get_usec(rules) \
			- rules->starting_time, philo->id);
	else if (message == DEAD)
		printf("%ld %d died\n", get_usec(rules) \
			- rules->starting_time, philo->id);
	pthread_mutex_unlock(&rules->lock_print);
}
