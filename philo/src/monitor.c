/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:36:47 by juhur             #+#    #+#             */
/*   Updated: 2022/03/27 19:26:23 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_alive(void *arg)
{
	t_info		*info = (t_info *)arg;

	while (!info->end)
	{
		for (int i = 0; i < info->philo_count; i++)
		{
			if (info->philo_full_count == info->philo_count)
				info->end = true;
			if (info->philo[i].state == STATE_PHILO_DEAD)
				continue ;
			if (info->philo[i].state == STATE_PHILO_FULL)
				continue ;
			if (get_elapsed_time(info) >= info->philo[i].last_meal_time + info->time_to_die)
			{
				print_action(info, DIED, i + 1);
				info->end = true;
				info->philo[i].state = STATE_PHILO_DEAD;
				return ((void *)0);
			}
		}
	}
	return ((void *)1);
}