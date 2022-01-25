/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonitor <gmonitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:40:30 by gmonitor          #+#    #+#             */
/*   Updated: 2022/01/25 18:42:53 by gmonitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	ft_usleep(int ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 920);
	while (ft_time() < time + ms)
		usleep(ms * 3);
}

time_t	get_usec(void)
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
		exit(0);
	sem_wait(rules->somebody_dead);
	sem_post(rules->somebody_dead);
	sem_wait(rules->write_sem);
	if (message == FORK)
		printf("%ld %d has taken a fork\n", get_usec() \
			- rules->starting_time, philo->id);
	else if (message == EAT)
		printf("%ld %d is eating\n", get_usec() \
			- rules->starting_time, philo->id);
	else if (message == SLEEP)
		printf("%ld %d is sleeping\n", get_usec() \
			- rules->starting_time, philo->id);
	else if (message == THINK)
		printf("%ld %d is thinking\n", get_usec() \
			- rules->starting_time, philo->id);
	else if (message == DEAD)
		printf("%ld %d died\n", get_usec() - rules->starting_time, philo->id);
	sem_post(rules->write_sem);
}

void	destroy_malloc(t_rules *rules)
{
	int	count;

	count = 0;
	free(&rules->pid_philos[0]);
	free(&rules->monitors_eating[0]);
	free(&rules->monitors_time[0]);
}
