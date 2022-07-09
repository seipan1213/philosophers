/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehattor <sehattor@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 22:31:26 by sehattor          #+#    #+#             */
/*   Updated: 2022/07/09 22:31:52 by sehattor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	ph;

	if (ph_init(argc, argv, &ph))
		return (1);
	ph_main(&ph);
	ph_end(&ph);
}
