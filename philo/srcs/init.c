#include "philo.h"

bool ph_check_args(t_philo *ph, int argc)
{
	if (ph->number_of_philosophers < 1 || ph->number_of_philosophers > 200)
		return (true);
	if (ph->time_to_die < 60)
		return (true);
	if (ph->time_to_eat < 60)
		return (true);
	if (ph->time_to_sleep < 60)
		return (true);
	if (argc == 6 && ph->number_of_times_each_philosopher_must_eat < 1)
		return (true);
	return (false);
}

bool ph_args_init(int argc, char **argv, t_philo *ph)
{
	if (argc != 5 && argc != 6)
		return (put_err(ARG_ERR));
	ph->number_of_philosophers = ph_atoi(argv[1]);
	ph->time_to_die = ph_atoi(argv[2]);
	ph->time_to_eat = ph_atoi(argv[3]);
	ph->time_to_sleep = ph_atoi(argv[4]);
	if (argc == 6)
		ph->number_of_times_each_philosopher_must_eat = ph_atoi(argv[5]);
	else
		ph->number_of_times_each_philosopher_must_eat = -1;
	if (ph_check_args(ph, argc))
		return (put_err(ARG_ERR));
	return (false);
}

bool ph_men_init(t_philo *ph)
{
	int num;
	int i;

	num = ph->number_of_philosophers;
	ph->men = malloc(sizeof(t_man) * num);
	if (ph->men == NULL)
		return (put_err(MALLOC_ERR));
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&ph->men[i].last_eat, NULL))
			return (put_err(MUTEX_ERR));
		ph->men[i].id = i + 1;
		ph->men[i].right = &ph->forks[i];
		ph->men[i].left = &ph->forks[(i + num - 1) % num];
		ph->men[i].fin = &ph->fin;
		ph->men[i].is_fin = &ph->is_fin;
		ph->men[i].eat = &ph->eat;
		ph->men[i].eat_cnt = &ph->eat_cnt;
		ph->men[i].print = &ph->print;
		ph->men[i].number_of_philosophers = ph->number_of_philosophers;
		ph->men[i].time_to_die = ph->time_to_die;
		ph->men[i].time_to_eat = ph->time_to_eat;
		ph->men[i].time_to_sleep = ph->time_to_sleep;
		ph->men[i].number_of_times_each_philosopher_must_eat = ph->number_of_times_each_philosopher_must_eat;
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
	if (pthread_mutex_init(&ph->fin, NULL))
		return (put_err(MUTEX_ERR));
	if (pthread_mutex_init(&ph->eat, NULL))
		return (put_err(MUTEX_ERR));
	if (pthread_mutex_init(&ph->print, NULL))
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
