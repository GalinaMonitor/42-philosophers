/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonitor <gmonitor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:52:51 by gmonitor          #+#    #+#             */
/*   Updated: 2022/01/25 19:30:42 by gmonitor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include "../libft/libft/libft.h"

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4

typedef struct s_philo
{
	int				id;
	int				left_ph;
	int				right_ph;
	int				meals_num;
	pthread_mutex_t	*first_f;
	pthread_mutex_t	*second_f;
	long long int	death_time_count;
	int				finish_meals;
}					t_philo;

typedef struct s_rules
{
	int				philo_id;
	int				philo_num;
	long long int	eating_time;
	long long int	death_time;
	long long int	sleeping_time;
	time_t			starting_time;
	int				finish_session;
	int				meals_num;
	t_philo			*philos;
	pthread_mutex_t	set_id;
	pthread_mutex_t	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock_print;
	pthread_t		*threads;
	pthread_t		*monitor;
}					t_rules;

void	init_philo(t_philo *philo, t_rules *rules);
void	init_rules(t_rules *rules, char **argv, int argc);
void	init_pthread(t_rules *rules);
void	init_mutex(t_rules *rules);
void	destroy_mutex(t_rules *rules);
void	destroy_pthread(t_rules *rules);
time_t	get_usec(t_rules *rules);
int		left(int n, int philo_num);
int		right(int n, int philo_num);
void	*philosopher(void *rules_raw);
void	*monitor_philo(void *rules_raw);
void	print_message(t_rules *rules, t_philo *philo, int message);
void	sleeping(t_rules *rules, t_philo *philo);
void	eating(t_rules *rules, t_philo *philo);
void	thinking(t_rules *rules, t_philo *philo);
void	ft_usleep(int ms);
long	ft_time(void);
void	ft_usleep(int ms);
int		left(int n, int philo_num);
int		right(int n, int philo_num);
void	destroy_malloc(t_rules *rules);
void	init_philos(t_rules *rules);
void	ft_check_args(void);
#endif
