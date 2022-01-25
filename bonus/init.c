/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonitor <gmonitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:40:11 by gmonitor          #+#    #+#             */
/*   Updated: 2022/01/25 19:35:12 by gmonitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_philo(int id, t_rules *rules)
{
	t_philo	philo;

	philo.id = id;
	philo.meals_num = rules->meals_num;
	philo.death_time_count = rules->starting_time;
	philo.finish_meals = 0;
	philo.left_ph = left(philo.id, rules->philo_num);
	philo.right_ph = right(philo.id, rules->philo_num);
	philo.rules = rules;
	rules->pid_philos[philo.id] = fork();
	if (rules->pid_philos[philo.id] == -1)
	{
		kill(rules->pid_philos[philo.id], SIGKILL);
		return (1);
	}
	else if (rules->pid_philos[philo.id] == 0)
		philosopher(rules, &philo);
	return (0);
}

void	init_rules(t_rules *rules, char **argv, int argc)
{
	if (argc < 2)
		return ;
	rules->philo_num = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->eating_time = ft_atoi(argv[3]);
	rules->sleeping_time = ft_atoi(argv[4]);
	rules->starting_time = get_usec();
	if (argv[5] != NULL)
		rules->meals_num = ft_atoi(argv[5]);
	else
		rules->meals_num = -1;
	rules->finish_session = 0;
	rules->monitors_eating = malloc(sizeof(pthread_t));
	rules->monitors_time = malloc(sizeof(pthread_t) * rules->philo_num);
	rules->pid_philos = malloc(sizeof(sem_t) * rules->philo_num);
}

void	init_sem(t_rules *rules)
{
	sem_unlink("fork_sem");
	sem_unlink("write_sem");
	sem_unlink("stop");
	sem_unlink("eat_enough");
	sem_unlink("eat_enough");
	sem_unlink("start");
	sem_unlink("somebody_dead");
	rules->fork_sem = sem_open("fork_sem", O_CREAT | \
		O_EXCL, S_IRWXU, rules->philo_num);
	rules->write_sem = sem_open("write_sem", O_CREAT | \
		O_EXCL, S_IRWXU, 1);
	rules->somebody_dead = sem_open("somebody_dead", O_CREAT | \
		O_EXCL, S_IRWXU, 1);
	rules->stop = sem_open("stop", O_CREAT | O_EXCL, S_IRWXU, 0);
	rules->start = sem_open("start", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (rules->meals_num >= 0)
		rules->eat_enough = sem_open("eat_enough", O_CREAT | \
			O_EXCL, S_IRWXU, 0);
}

void	init_philos(t_rules *rules)
{
	int	count;

	count = 0;
	while (count < rules->philo_num)
		init_philo(count++, rules);
	sem_post(rules->start);
	if (rules->meals_num > 0)
	{
		pthread_create(rules->monitors_eating, NULL, monitor_eating, rules);
		pthread_detach(*rules->monitors_eating);
	}
}
