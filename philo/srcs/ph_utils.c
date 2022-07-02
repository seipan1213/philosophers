
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
		pthread_mutex_destroy(&ph->forks[i]);
	pthread_mutex_destroy(&ph->fin);
	pthread_mutex_destroy(&ph->eat);
	ph_free(ph, 0);
}

void ph_put_log(t_man *man, char *str)
{
	long time;

	if (is_finish(man))
		return;
	time = get_time_ms();
	printf("%ld %d %s\n", time, man->id, str);
}
