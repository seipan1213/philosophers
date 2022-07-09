#include "philo.h"

void ph_watcher(void *arg)
{
	long time;
	int i;
	int fin_cnt;
	t_philo *ph;

	ph = (t_philo *)arg;
	while (!get_is_fin(&ph->men[0]))
	{
		i = -1;
		fin_cnt = 0;
		while (++i < ph->number_of_philosophers)
		{
			time = get_time_ms();
			if (time - get_last_eat_time(&ph->men[i]) >= ph->time_to_die)
			{
				pthread_mutex_lock(&ph->fin);
				pthread_mutex_lock(&ph->print);
				if (!ph->is_fin)
					printf("%ld %d %s\n", get_time_ms(), ph->men[i].id, DIED);
				ph->is_fin = true;
				pthread_mutex_unlock(&ph->print);
				pthread_mutex_unlock(&ph->fin);
				return;
			}
			else if (ph->number_of_times_each_philosopher_must_eat > 0 && get_eat_cnt(&ph->men[i]) >= ph->number_of_times_each_philosopher_must_eat)
				fin_cnt++;
		}
		if (fin_cnt == ph->number_of_philosophers)
		{
			set_is_fin(&ph->men[0], true);
			return;
		}
		usleep(100);
	}
	return;
}