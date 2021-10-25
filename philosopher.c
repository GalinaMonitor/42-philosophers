# include "philosopher.h"

enum states { hungry, eating, thinking, sleeping };
int counter = 0;

int	left(int n) { return (n - 1 + 5) % 5; }
int	right(int n) { return (n + 1) % 5; }



void	*philosopher(void *philo_raw)
{
	t_philo *philo = (t_philo *)philo_raw;

	while (1)
	{
		usleep(500 * philo->id);
		pthread_mutex_lock(philo->left_f);
		printf("LFORK - %d\n", philo->id);
		pthread_mutex_lock(philo->right_f);
		printf("RFORK - %d\n", right(philo->id));
		usleep(40);
		pthread_mutex_unlock(philo->left_f);
		printf("LFORKOFF - %d\n", philo->id);
		pthread_mutex_unlock(philo->right_f);
		printf("RFORKOFF - %d\n", philo->id);
		usleep(40);
	}
	return NULL;
}



int	main()
{
	pthread_t		threads[5];
	int				count;
	t_philo			philo[5];
	pthread_mutex_t	mutex[5];

	int phi_state[5] = { thinking, thinking, thinking, thinking, thinking };
	count = 0;

	while (count < 5)
		pthread_mutex_init(&(mutex[count++]), NULL);
	count = 0;

	while (count < 4)
	{
		philo[count].forks = mutex;
		philo[count].philosophers = philo;

		philo[count].id = count;

		philo[count].left_f = &mutex[count];
		philo[count].right_f = &mutex[right(count)];

		philo[count].left_ph = left(count);
		philo[count].right_ph = right(count);
		count++;
	}
	philo[count].forks = mutex;
	philo[count].philosophers = philo;

	philo[count].id = count;

	philo[count].right_f = &mutex[count];
	philo[count].left_f = &mutex[right(count)];

	philo[count].left_ph = left(count);
	philo[count].right_ph = right(count);
	count = 0;

	while (count < 5)
	{
		pthread_create(&threads[count], NULL, philosopher, &philo[count]);
		count++;
	}
	count = 0;

	while (count < 5)
		pthread_join(threads[count++], NULL);
	count = 0;

	while (count < 5)
		pthread_mutex_destroy(&mutex[count++]);

	return 0;
}
