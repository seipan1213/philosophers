#include "philo.h"

void ph_work_think(t_man *man)
{
	ph_put_log(man, THINKING);
}

void ph_work_eat(t_man *man)
{
	long start;

	pthread_mutex_lock(man->right);

	start = get_time_ms();
	ph_put_log(man, PIC_FORK);
	start = get_time_ms() - start;
	pthread_mutex_lock(man->left);
	start = get_time_ms() - start;
	ph_put_log(man, PIC_FORK);
	ph_put_log(man, EATING);
	eat_cnt_update(man, 1);
	last_etime_update(man);
	man_sleep(man->time_to_eat - (get_time_ms() - start), man);
	pthread_mutex_unlock(man->right);
	pthread_mutex_unlock(man->left);
}

void ph_work_sleep(t_man *man)
{
	long start;

	start = get_time_ms();
	ph_put_log(man, SLEEPING);
	man_sleep(man->time_to_sleep - (get_time_ms() - start), man);
}

void *ph_work(void *arg)
{
	t_man *man;

	man = (t_man *)arg;
	last_etime_update(man);
	if (man->id % 2 == 1)
		usleep(TIME_INTERVAL);
	while (!is_finish(man))
	{
		ph_work_eat(man);
		ph_work_sleep(man);
		ph_work_think(man);
	}
	return (NULL);
}

void ph_main(t_philo *ph)
{
	int i;

	while (get_time_ms() % 100 != 0)
		;
	i = -1;
	while (++i < ph->number_of_philosophers)
		pthread_create(&ph->men[i].thread, NULL, ph_work, &ph->men[i]);
	usleep(10);
	i = -1;
	while (++i < ph->number_of_philosophers)
		pthread_create(&ph->men[i].watcher, NULL, ph_watcher, &ph->men[i]);
	i = -1;
	while (++i < ph->number_of_philosophers)
	{
		pthread_join(ph->men[i].thread, NULL);
		pthread_join(ph->men[i].watcher, NULL);
	}
}