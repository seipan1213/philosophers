/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_watcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:32:41 by sehattor          #+#    #+#             */
/*   Updated: 2022/07/09 23:31:55 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_watcher_util(t_philo *ph, int i, int *fin_cnt)
{
	if (get_time_ms() - get_last_eat_time(&ph->men[i]) >= ph->time_to_die)
	{
		pthread_mutex_lock(&ph->print);
		pthread_mutex_lock(&ph->fin);
		if (!ph->is_fin)
			printf("%ld %d %s\n", get_time_ms(), ph->men[i].id, DIED);
		ph->is_fin = true;
		pthread_mutex_unlock(&ph->fin);
		pthread_mutex_unlock(&ph->print);
		return (true);
	}
	else if (ph->number_of_times_each_philosopher_must_eat > 0
		&& get_eat_cnt(&ph->men[i])
		>= ph->number_of_times_each_philosopher_must_eat)
		(*fin_cnt)++;
	return (false);
}

void	ph_watcher(void *arg)
{
	t_philo	*ph;
	int		i;
	int		fin_cnt;

	ph = (t_philo *)arg;
	while (!get_is_fin(&ph->men[0]))
	{
		i = -1;
		fin_cnt = 0;
		while (++i < ph->number_of_philosophers)
		{
			if (ph_watcher_util(ph, i, &fin_cnt))
				return ;
		}
		if (fin_cnt == ph->number_of_philosophers)
		{
			set_is_fin(&ph->men[0], true);
			return ;
		}
		usleep(100);
	}
	return ;
}
