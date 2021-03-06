/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:31:26 by sehattor          #+#    #+#             */
/*   Updated: 2022/07/10 11:58:11 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_main(t_philo *ph)
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
			return (put_err(MUTEX_ERR));
		}
	}
	while (get_time_ms() % 100 != 0)
		;
	pthread_mutex_unlock(&ph->fin);
	ph_watcher(ph);
	i = -1;
	while (++i < ph->number_of_philosophers)
		pthread_join(ph->men[i].thread, NULL);
	return (false);
}

int	main(int argc, char **argv)
{
	t_philo	ph;

	if (ph_init(argc, argv, &ph))
		return (1);
	if (ph_main(&ph))
	{
		ph_end(&ph);
		return (1);
	}
	ph_end(&ph);
}
