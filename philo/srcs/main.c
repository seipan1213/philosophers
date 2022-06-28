#include "philo.h"

bool ph_args_init(int argc, char **argv, t_philo *ph)
{
	if (argc != 5 && argc != 6)
		return (put_err(ARG_ERR));
	ph->number_of_philosophers = ft_atoi(argv[1]);
	ph->time_to_die = ft_atoi(argv[2]);
	ph->time_to_eat = ft_atoi(argv[3]);
	ph->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ph->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	// TODO: argv 数値判定
	return (false);
}

bool ph_men_init(t_philo *ph)
{
	int num;
	int i;

	i = -1;
	num = ph->number_of_philosophers;
	ph->men = malloc(sizeof(t_men) * num);
	if (ph->men == NULL)
		return (put_err(MALLOC_ERR));
	while (++i < num)
	{
		ph->men[i].right = &ph->forks[i];
		ph->men[i].left = &ph->forks[(i + num - 1) % num];
		ph->men[i].died = &ph->died;
		ph->men[i].eat = &ph->eat;
		ph->men[i].eat_cnt = &ph->eat_cnt;
	}
	return (false);
}

bool ph_main_init(t_philo *ph)
{
	int num;
	int i;

	num = ph->number_of_philosophers;
	ph->forks = malloc((sizeof(pthread_mutex_t) * num));
	if (ph->forks == NULL)
		return (put_err(MALLOC_ERR));
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&ph->forks[i], NULL))
			return (put_err(MUTEX_ERR));
	}
	if (pthread_mutex_init(&ph->died, NULL))
		return (put_err(MUTEX_ERR));
	if (pthread_mutex_init(&ph->eat, NULL))
		return (put_err(MUTEX_ERR));
	return (false);
}

bool ph_init(int argc, char **argv, t_philo *ph)
{
	ft_bzero(ph, sizeof(t_philo));
	if (ph_args_init(argc, argv, ph))
		return (true);
	if (ph_main_init(ph))
		return (ph_free(ph, true));
	if (ph_men_init(ph))
		return (ph_free(ph, true));
	return (false);
}

int ph_free(t_philo *ph, int ret)
{
	if (ph->forks != NULL)
		free(ph->forks);
	if (ph->men != NULL)
		free(ph->men);
	return (ret);
}
void ph_mutex_destoy(t_philo *ph)
{
	int i;

	i = -1;
	while (++i < ph->number_of_philosophers)
		pthread_mutex_destroy(&ph->forks[i]);
	pthread_mutex_destroy(&ph->died);
	pthread_mutex_destroy(&ph->eat);
}
int main(int argc, char **argv)
{
	t_philo ph;

	if (ph_init(argc, argv, &ph))
		return (1);
	printf("%d  %d  %d  %d  %d\n", ph.number_of_philosophers, ph.time_to_die, ph.time_to_eat, ph.time_to_sleep, ph.number_of_times_each_philosopher_must_eat);
	ph_mutex_destoy(&ph);
	return (ph_free(&ph, 0));
}