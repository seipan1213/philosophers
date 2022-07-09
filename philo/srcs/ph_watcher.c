#include "philo.h"

void *ph_watcher(void *arg)
{
	long time;
	t_man *man;

	man = (t_man *)arg;
	while (!get_is_fin(man))
	{
		time = get_time_ms();
		if (time - get_last_eat_time(man) >= man->time_to_die)
		{
			pthread_mutex_lock(man->fin);
			if (!(*man->is_fin))
				printf("%ld %d %s\n", time, man->id, DIED);
			*man->is_fin = true;
			pthread_mutex_unlock(man->fin);
		}
		else if (man->number_of_times_each_philosopher_must_eat > 0 && get_eat_cnt(man) >= man->number_of_times_each_philosopher_must_eat * man->number_of_philosophers)
			set_is_fin(man, true);
	}
	return (NULL);
}