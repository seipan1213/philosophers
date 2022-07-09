
#include "philo.h"

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
