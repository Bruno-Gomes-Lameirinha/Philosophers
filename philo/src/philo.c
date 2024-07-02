#include "../includes/philo.h"

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

int main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		ft_wrong_args();
		return(1);
	}
	else
	{
		printf("%s\n",argv[1]);
		printf("right number of ags\n");
		//checar os argumentos;
		// inciciar a as threads
		//  numeros de garfos == numeros de filosofos
		//eat, think, sleep
		// mutex nos garfos
	}
	return(0);
}