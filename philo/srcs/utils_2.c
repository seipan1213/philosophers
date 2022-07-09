#include "philo.h"

void man_sleep(long sleep_time, t_man *man)
{
	long start;
	long now;

	start = get_time_ms();
	now = start;
	while ((now - start) < sleep_time)
	{
		if (get_is_fin(man))
			return;
		usleep(100);
		now = get_time_ms();
	}
	return;
}

int get_eat_cnt(t_man *man)
{
	int eat_cnt;

	pthread_mutex_lock(&man->eat);
	eat_cnt = (*man->eat_cnt);
	pthread_mutex_unlock(&man->eat);
	return (eat_cnt);
}

bool get_is_fin(t_man *man)
{
	bool is_fin;

	pthread_mutex_lock(man->fin);
	is_fin = *man->is_fin;
	pthread_mutex_unlock(man->fin);
	return (is_fin);
}

void set_is_fin(t_man *man, bool is_fin)
{
	pthread_mutex_lock(man->fin);
	*man->is_fin = is_fin;
	pthread_mutex_unlock(man->fin);
}

long get_last_eat_time(t_man *man)
{
	long last_eat_time;

	pthread_mutex_lock(&man->eat);
	last_eat_time = man->last_eat_time;
	pthread_mutex_unlock(&man->eat);
	return (last_eat_time);
}

void set_last_eat_time(t_man *man)
{
	pthread_mutex_lock(&man->eat);
	man->last_eat_time = get_time_ms();
	man->eat_cnt++;
	pthread_mutex_unlock(&man->eat);
}
