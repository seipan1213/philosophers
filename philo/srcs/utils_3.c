/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:35:42 by sehattor          #+#    #+#             */
/*   Updated: 2022/07/09 23:09:34 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_eat_cnt(t_man *man)
{
	int	eat_cnt;

	pthread_mutex_lock(&man->eat);
	eat_cnt = man->eat_cnt;
	pthread_mutex_unlock(&man->eat);
	return (eat_cnt);
}

bool	get_is_fin(t_man *man)
{
	bool	is_fin;

	pthread_mutex_lock(man->fin);
	is_fin = *man->is_fin;
	pthread_mutex_unlock(man->fin);
	return (is_fin);
}

void	set_is_fin(t_man *man, bool is_fin)
{
	pthread_mutex_lock(man->fin);
	*man->is_fin = is_fin;
	pthread_mutex_unlock(man->fin);
}

long	get_last_eat_time(t_man *man)
{
	long	last_eat_time;

	pthread_mutex_lock(&man->eat);
	last_eat_time = man->last_eat_time;
	pthread_mutex_unlock(&man->eat);
	return (last_eat_time);
}

void	set_last_eat_time(t_man *man, bool is_cnt)
{
	pthread_mutex_lock(&man->eat);
	man->last_eat_time = get_time_ms();
	if (is_cnt)
		man->eat_cnt++;
	pthread_mutex_unlock(&man->eat);
}
