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
	printf("|               Wrong number of ags                  |\n");
	printf("| ___________________________________________________|\n");
	printf("|            Please enter 4 or 5 arguments           |\n");
	printf("|____________________________________________________|\n");
	printf("|             [1][Number of philosophers]            |\n");
	printf("|             [2][Time to die]                       |\n");
	printf("|             [3][Time to eat]                       |\n");
	printf("|             [4][Time to sleep]                     |\n");
	printf("|             [5][Number of meals]                   |\n");
	printf("|____________________________________________________|\n");
	printf("\n");
}

void	ft_free_memory(t_args *args)
{
	free(args->forks);
	free(args->ph);
	free (args);
}

void	ft_init_args(t_args *args, char **argv, int argc)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (!ft_is_num(argv[i]))
		{
			ft_free_memory(args);
			printf("Non numeric argument found\n");
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

	printf("Thread %d acessando routine in %lld miliseconds\n", philo->id, (current_time() - philo->epoch));
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
		printf("fork %d has been created\n", i);
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
		printf("Trhead %d has been created\n", i);
		i++;
	}
	i = 0;
	while (i < args->n_philo)
	{
		pthread_join(args->ph[i].philo, NULL);
		printf("Trhead %d has finished his execution in %lld miliseconds\n", i, (current_time() - args->ph[i].epoch));
		i++;
	}
}

int main(int argc, char **argv)
{
	t_args	*args;

	args = (t_args *)malloc(sizeof(t_args));

	if (argc != 5 && argc != 6)
	{
		ft_wrong_args();
		return(1);
	}
	else
	{
		ft_init_args(args, argv, argc);
		ft_init_philos(args);
		// printf("%d\n", args->time_to_die);
		// printf("%d\n", args->time_to_eat);
		// printf("%d\n", args->time_to_sleep);
		// if ( argc == 6)
		// 	printf("%d\n", args->n_times_to_eat);
		// inciciar a as threads
		//  numeros de garfos == numeros de filosofos
		//eat, think, sleep
		// mutex nos garfos
	}
	ft_destroy_forks(args);
	ft_free_memory(args);
	return(0);
}
