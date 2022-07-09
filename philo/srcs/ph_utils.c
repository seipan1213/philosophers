
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

int ph_free(t_philo *ph, int ret)
{
	if (ph->forks != NULL)
		free(ph->forks);
	if (ph->men != NULL)
		free(ph->men);
	return (ret);
}

void ph_end(t_philo *ph)
{
	int i;

	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		pthread_mutex_destroy(&ph->forks[i]);
		pthread_mutex_destroy(&ph->men[i].eat);
	}
	pthread_mutex_destroy(&ph->fin);
	pthread_mutex_destroy(&ph->print);
	ph_free(ph, 0);
}

void ph_put_log(t_man *man, char *str)
{
	long time;

	pthread_mutex_lock(man->print);
	if (get_is_fin(man))
	{
		pthread_mutex_unlock(man->print);
		return;
	}
	time = get_time_ms();
	printf("%ld %d %s\n", time, man->id, str);
	pthread_mutex_unlock(man->print);
}

void men_thread_detach(t_man *men, int size)
{
	int i;

	i = -1;
	while (++i < size)
		pthread_detach(men[i].thread);
}