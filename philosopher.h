# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct		s_philo
{
	int				id;
	int				left_ph;
	int				right_ph;

	struct s_philo	*philosophers;

	pthread_mutex_t	*forks;

	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;

}					t_philo;
