#include "../includes/philo.h"

long long current_time(void)
{
	struct timeval timestamp;
	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000LL + timestamp.tv_usec / 1000);
}

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
	{
		return (0);
	}
	return (1);
}

int	ft_is_num(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '-')
		i++;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_wrong_args(void)
{
	printf(" ____________________________________________________ \n");
	printf("|               Wrong number of args                  |\n");
	printf("| ___________________________________________________|\n");
	printf("|            Please enter 4 or 5 arguments           |\n");
	printf("|____________________________________________________|\n");
	printf("|             [1][Number of philosophers]            |\n");
	printf("|             [2][Time to die]                       |\n");
	printf("|             [3][Time to eat]                       |\n");
	printf("|             [4][Time to sleep]                     |\n");
	printf("|             [5][Number of meals]                   |\n");
	printf("|             *Times must be expressed in Miliseconds|\n");
	printf("|____________________________________________________|\n");
	printf("\n");
}

void	ft_free_memory(t_args *args)
{
	if (args->forks)
		free(args->forks);
	if (args->ph)
		free(args->ph);
	free (args);
}

void	ft_init_args(t_args *args, char **argv, int argc)
{
	int i;

	i = 1;
	while (i < argc)
	{
		args->n_philo = 0;
		args->time_to_die = 0;
		if (!ft_is_num(argv[i]))
		{
			free(args);
			printf("Non numeric argument found\n");
			ft_wrong_args();
			exit(1);
		}
		i++;
	}
	args->n_philo = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		args->n_times_to_eat = atoi(argv[5]);
	
}
void *ft_philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	philo->last_meal = current_time();
	while ((current_time() - philo->last_meal) < philo->rules->time_to_die)
	{
		if (philo->id % 2 == 0)
    	{
       		pthread_mutex_lock(philo->r_fork);
        	pthread_mutex_lock(philo->l_fork);
    	}
    	else	
    	{
        	pthread_mutex_lock(philo->l_fork);
        	pthread_mutex_lock(philo->r_fork);
    	}
		printf("%lld Philospher %d got the fork \n", (current_time() - philo->epoch), philo->id);
		printf("%lld Philospher %d is eating \n", (current_time() - philo->epoch), philo->id);
		usleep(philo->rules->time_to_eat * 1000);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		philo->last_meal = current_time();
		ft_think(philo);
	}
	return(NULL);
}

void	ft_init_forks(t_args *args)
{
	int	i;

	i = 0;
	args->forks = malloc(sizeof(pthread_mutex_t) * args->n_philo);
	while (i < args->n_philo)
	{
		pthread_mutex_init(&args->forks[i], NULL);
		pthread_mutex_init(&args->ph[i].reaper, NULL);
		i++;
	}
}

void	ft_destroy_forks(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->n_philo)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&args->ph[i].reaper);
		i++;
	}
}

void	ft_init_philos(t_args *args)
{
	int	i;

	args->ph = malloc(sizeof(t_philo) * args->n_philo);
	i = 0;
	ft_init_forks(args);
	while (i < args->n_philo)
	{
		args->ph[i].id = i + 1;
		args->ph[i].epoch = current_time();
		args->ph[i].rules = args;
		args->ph[i].l_fork = &args->forks[i];
		args->ph[i].r_fork = &args->forks[(i + 1) % args->n_philo];
		pthread_create(&args->ph[i].philo, NULL, &ft_philo_routine, (void*)&args->ph[i]);
		i++;
	}
	i = 0;
	while (i < args->n_philo)
	{
		pthread_join(args->ph[i].philo, NULL);
		i++;
	}
}

void	ft_think(t_philo *args)
{
	printf("%lld Philospher %d is sleeping \n", (current_time() - args->epoch), args->id);
	usleep(args->rules->time_to_sleep * 1000);
	printf("%lld Philospher %d is thinking \n", (current_time() - args->epoch), args->id);

}

int main(int argc, char **argv)
{
	t_args	*args;

	if (argc != 5 && argc != 6)
	{
		ft_wrong_args();
		return(1);
	}
	else
	{
		args = (t_args *)malloc(sizeof(t_args));
		ft_init_args(args, argv, argc);
		ft_init_philos(args);
	}
	ft_destroy_forks(args);
	ft_free_memory(args);
	return(0);
}
