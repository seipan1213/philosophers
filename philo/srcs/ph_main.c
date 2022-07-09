/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:38:25 by sehattor          #+#    #+#             */
/*   Updated: 2022/07/09 22:39:26 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_work_think(t_man *man)
{
	if (get_is_fin(man))
		return ;
	ph_put_log(man, THINKING);
}

void	ph_work_eat(t_man *man)
{
	long	start;

	if (man->id % 2)
		pthread_mutex_lock(man->right);
	else
		pthread_mutex_lock(man->left);
	ph_put_log(man, PIC_FORK);
	if (man->right == man->left)
	{
		man_sleep(man->time_to_die, man);
		pthread_mutex_unlock(man->right);
		return ;
	}
	if (man->id % 2)
		pthread_mutex_lock(man->left);
	else
		pthread_mutex_lock(man->right);
	start = get_time_ms();
	ph_put_log(man, PIC_FORK);
	ph_put_log(man, EATING);
	set_last_eat_time(man);
	man_sleep(man->time_to_eat - (get_time_ms() - start), man);
	pthread_mutex_unlock(man->right);
	pthread_mutex_unlock(man->left);
}

void	ph_work_sleep(t_man *man)
{
	long	start;

	start = get_time_ms();
	if (get_is_fin(man))
		return ;
	ph_put_log(man, SLEEPING);
	man_sleep(man->time_to_sleep - (get_time_ms() - start), man);
}

void	*ph_work(void *arg)
{
	t_man	*man;

	man = (t_man *)arg;
	set_last_eat_time(man);
	get_is_fin(man);
	if (man->id % 2 == 1)
		man_sleep(man->time_to_eat / 2, man);
	while (!get_is_fin(man))
	{
		ph_work_eat(man);
		ph_work_sleep(man);
		ph_work_think(man);
	}
	return (NULL);
}

void	ph_main(t_philo *ph)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&ph->fin);
	while (++i < ph->number_of_philosophers)
	{
		if (pthread_create(&ph->men[i].thread, NULL, ph_work, &ph->men[i]) != 0)
		{
			men_thread_detach(ph->men, i);
			pthread_mutex_unlock(&ph->fin);
			return ;
		}
	}
	while (get_time_ms() % 100 != 0)
		;
	pthread_mutex_unlock(&ph->fin);
	ph_watcher(ph);
	i = -1;
	while (++i < ph->number_of_philosophers)
		pthread_join(ph->men[i].thread, NULL);
}
