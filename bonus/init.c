#include "philosopher.h"

int	init_philo(t_philo *philo, t_rules *rules)
{
	philo->id = rules->philo_id;
	rules->philo_id++;
	philo->meals_num = rules->meals_num;
	philo->death_time_count = rules->starting_time;
	philo->finish_meals = 0;
	philo->left_ph = left(philo->id, rules->philo_num);
	philo->right_ph = right(philo->id, rules->philo_num);
	rules->pid_philos[philo->id] = fork();
	if (rules->pid_philos[philo->id] == -1)
		return (1);
	else if (rules->pid_philos[philo->id] == 0)
		philosopher(rules, philo);
	return 0;
}

void	init_rules(t_rules *rules, char **argv, int argc)
{
	if (argc < 2)
		return ;

	rules->philo_num = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->eating_time = ft_atoi(argv[3]);
	rules->sleeping_time = ft_atoi(argv[4]);
	rules->starting_time = get_usec(rules);
	if (argv[5] != NULL)
		rules->meals_num = ft_atoi(argv[5]);
	else
		rules->meals_num = -1;
	rules->philo_id = 0;
	rules->finish_session = 0;
	rules->pid_philos = malloc(sizeof(sem_t) * rules->philo_num);
	rules->philos = malloc(sizeof(t_philo) * rules->philo_num);
}

void	init_sem(t_rules *rules)
{
	rules->fork_sem = sem_open("fork_sem", O_CREAT | O_EXCL, S_IRWXU, rules->philo_num);
	rules->write_sem = sem_open("write_sem", O_CREAT | O_EXCL, S_IRWXU, 1);
	rules->stop = sem_open("stop", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (rules->meals_num >= 0)
		rules->eat_enough = sem_open("eat_enough", O_CREAT | O_EXCL, S_IRWXU, 0);
}

void	init_philos(t_rules *rules)
{
	int count;
	pthread_t	*monitor;

	count = 0;
	while (count < rules->philo_num)
		init_philo(&rules->philos[count++], rules);
	monitor = malloc(sizeof(pthread_mutex_t));
	pthread_create(monitor, NULL, monitor_philo, rules);
	rules->monitor = monitor;
}
