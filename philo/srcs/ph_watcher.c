#include "philo.h"

void *ph_watcher(void *arg)
{
	long time;
	t_man *man;

	man = (t_man *)arg;
	while (true)
	{
		time = get_time_ms();
		pthread_mutex_lock(&man->last_eat);
		pthread_mutex_lock(man->eat);
		if (time - man->last_eat_time >= man->time_to_die)
		{
			pthread_mutex_lock(man->fin);
			if (!(*man->is_fin))
				printf("%ld %d %s\n", time, man->id, DIED);
			*man->is_fin = true;
			pthread_mutex_unlock(man->fin);
		}
		else if (man->number_of_times_each_philosopher_must_eat > 0 && *man->eat_cnt >= man->number_of_times_each_philosopher_must_eat * man->number_of_philosophers)
		{
			pthread_mutex_lock(man->fin);
			*man->is_fin = true;
			pthread_mutex_unlock(man->fin);
		}
		pthread_mutex_unlock(&man->last_eat);
		pthread_mutex_unlock(man->eat);
		if (is_finish(man))
			break;
	}
	return (NULL);
}