#include "philo.h"

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
	printf("%d\n", *man->eat_cnt);
	pthread_mutex_unlock(man->eat);
}

bool ph_args_init(int argc, char **argv, t_philo *ph)
{
	if (argc != 5 && argc != 6)
		return (put_err(ARG_ERR));
	ph->number_of_philosophers = ft_atoi(argv[1]);
	ph->time_to_die = ft_atoi(argv[2]);
	ph->time_to_eat = ft_atoi(argv[3]);
	ph->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		ph->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		ph->number_of_times_each_philosopher_must_eat = -1;
	// TODO: argv 数値判定
	return (false);
}

bool ph_men_init(t_philo *ph)
{
	int num;
	int i;

	num = ph->number_of_philosophers;
	ph->men = malloc(sizeof(t_man) * num);
	if (ph->men == NULL)
		return (put_err(MALLOC_ERR));
	i = -1;
	while (++i < num)
	{
		ph->men[i].id = i + 1;
		ph->men[i].right = &ph->forks[i];
		ph->men[i].left = &ph->forks[(i + num - 1) % num];
		ph->men[i].fin = &ph->fin;
		ph->men[i].is_fin = &ph->is_fin;
		ph->men[i].eat = &ph->eat;
		ph->men[i].eat_cnt = &ph->eat_cnt;
		ph->men[i].number_of_philosophers = ph->number_of_philosophers;
		ph->men[i].time_to_die = ph->time_to_die;
		ph->men[i].time_to_eat = ph->time_to_eat;
		ph->men[i].time_to_sleep = ph->time_to_sleep;
		ph->men[i].number_of_times_each_philosopher_must_eat = ph->number_of_times_each_philosopher_must_eat;
	}
	return (false);
}

bool ph_main_init(t_philo *ph)
{
	int num;
	int i;

	num = ph->number_of_philosophers;
	ph->forks = malloc((sizeof(pthread_mutex_t) * num));
	if (ph->forks == NULL)
		return (put_err(MALLOC_ERR));
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&ph->forks[i], NULL))
			return (put_err(MUTEX_ERR));
	}
	if (pthread_mutex_init(&ph->fin, NULL))
		return (put_err(MUTEX_ERR));
	if (pthread_mutex_init(&ph->eat, NULL))
		return (put_err(MUTEX_ERR));
	return (false);
}

bool ph_init(int argc, char **argv, t_philo *ph)
{
	ft_bzero(ph, sizeof(t_philo));
	if (ph_args_init(argc, argv, ph))
		return (true);
	if (ph_main_init(ph))
		return (ph_free(ph, true));
	if (ph_men_init(ph))
		return (ph_free(ph, true));
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
		pthread_mutex_destroy(&ph->forks[i]);
	pthread_mutex_destroy(&ph->fin);
	pthread_mutex_destroy(&ph->eat);
	ph_free(ph, 0);
}

void ph_put_log(t_man *man, char *str)
{
	long time;

	pthread_mutex_lock(man->fin);
	if (*man->is_fin)
	{
		pthread_mutex_unlock(man->fin);
		return;
	}
	time = get_time_ms();
	printf("%ld %d %s\n", time, man->id, str);
	pthread_mutex_unlock(man->fin);
}

void ph_work_think(t_man *man)
{
	ph_put_log(man, THINKING);
}

void ph_work_eat(t_man *man)
{
	long start;

	if (man->id % 2 == 0)
		pthread_mutex_lock(man->right);
	else
		pthread_mutex_lock(man->left);
	start = get_time_ms();
	ph_put_log(man, PIC_FORK);
	start = get_time_ms() - start;
	if (man->id % 2 == 0)
		pthread_mutex_lock(man->left);
	else
		pthread_mutex_lock(man->right);
	start = get_time_ms() - start;
	ph_put_log(man, PIC_FORK);
	ph_put_log(man, EATING);
	last_etime_update(man);
	eat_cnt_update(man, 1);
	ms_sleep(man->time_to_eat - (get_time_ms() - start));
	pthread_mutex_unlock(man->right);
	pthread_mutex_unlock(man->left);
}

void ph_work_sleep(t_man *man)
{
	long start;

	start = get_time_ms();
	ph_put_log(man, SLEEPING);
	ms_sleep(man->time_to_sleep - (get_time_ms() - start));
}

void *ph_work(void *arg)
{
	t_man *man;

	man = (t_man *)arg;
	last_etime_update(man);
	if (man->id % 2 == 1)
		usleep(TIME_INTERVAL);
	while (!(*man->is_fin))
	{
		ph_work_eat(man);
		ph_work_sleep(man);
		ph_work_think(man);
	}
	pthread_mutex_unlock(man->fin);
	return (NULL);
}

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
		else if (man->number_of_times_each_philosopher_must_eat > 0 && *man->eat_cnt >= man->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_lock(man->fin);
			*man->is_fin = true;
			pthread_mutex_unlock(man->fin);
		}
		pthread_mutex_unlock(&man->last_eat);
		pthread_mutex_unlock(man->eat);
		pthread_mutex_lock(man->fin);
		if (*man->is_fin)
		{
			pthread_mutex_unlock(man->fin);
			break;
		}
		pthread_mutex_unlock(man->fin);
	}
	return (NULL);
}

void ph_main(t_philo *ph)
{
	int i;

	while (get_time_ms() % 10 != 0)
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

int main(int argc, char **argv)
{
	t_philo ph;

	if (ph_init(argc, argv, &ph))
		return (1);
	ph_main(&ph);
	ph_end(&ph);
}