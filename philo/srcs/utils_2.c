#include "philo.h"

long get_time_ms(void)
{
	struct timeval time;
	long msec;

	gettimeofday(&time, NULL);
	msec = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (msec);
}

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