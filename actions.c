#include "philosopher.h"

void	eating(t_rules *rules, t_philo *philo)
{
	pthread_mutex_lock(philo->first_f);
	print_message(rules, philo, FORK);
	pthread_mutex_lock(philo->second_f);
	print_message(rules, philo, FORK);
	print_message(rules, philo, EAT);
	philo->death_time_count = get_usec(rules);
	ft_usleep(rules->eating_time);
	if (philo->meals_num >= 0)
		philo->meals_num--;
	pthread_mutex_unlock(philo->first_f);
	pthread_mutex_unlock(philo->second_f);
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
