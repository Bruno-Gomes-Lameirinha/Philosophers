#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "philo.h"

typedef struct s_philo
{
	int				id;
	long long		last_meal;
	pthread_t		philo;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	reaper;
	int				times_eaten;
	struct t_args	*rules;
}	t_philo;

typedef struct args
{
	int	n_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int n_times_to_eat;
	t_philo			*ph;
}	t_args;

void    ft_wrong_args(void);
void	ft_free_memory(t_args *args);
void	ft_init_args(t_args *args, char **argv, int argc);
int		ft_is_num(char *num);
int		ft_isdigit(int c);
void	ft_init_philos(t_args *args);
void *ft_philo_routine(void *arg);
#endif