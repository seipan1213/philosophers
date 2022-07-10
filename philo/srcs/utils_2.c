/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:31:58 by sehattor          #+#    #+#             */
/*   Updated: 2022/07/10 12:13:32 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	time;
	long long		msec;

	gettimeofday(&time, NULL);
	msec = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (msec);
}

void	man_sleep(long long sleep_time, t_man *man)
{
	long long	start;
	long long	now;

	start = get_time_ms();
	now = start;
	while ((now - start) < sleep_time)
	{
		if (get_is_fin(man))
			return ;
		usleep(100);
		now = get_time_ms();
	}
	return ;
}
