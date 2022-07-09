#include "philo.h"

void man_sleep(long sleep_time, t_man *man)
{
	long start;
	long now;

	start = get_time_ms();
	now = start;
	while ((now - start) < sleep_time)
	{
		if (is_finish(man))
			return;
		usleep(100);
		now = get_time_ms();
	}
	return;
}

void last_etime_update(t_man *man)
{
	pthread_mutex_lock(&man->last_eat);
	man->last_eat_time = get_time_ms();
	pthread_mutex_unlock(&man->last_eat);
}

void eat_cnt_update(t_man *man, int inc)
{
	pthread_mutex_lock(man->eat);
	(*man->eat_cnt) += inc;
	pthread_mutex_unlock(man->eat);
}

bool is_finish(t_man *man)
{
	bool is_fin;

	pthread_mutex_lock(man->fin);
	is_fin = *man->is_fin;
	pthread_mutex_unlock(man->fin);
	return (is_fin);
}