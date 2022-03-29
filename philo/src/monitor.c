/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:36:47 by juhur             #+#    #+#             */
/*   Updated: 2022/03/29 10:36:46 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_alive(void *arg)
{
	t_info		*info;
	int			i;
	long long	cur;

	info = (t_info *)arg;
	while (!info->end)
	{
		i = -1;
		while (++i < info->philo_count)
		{
			if (info->philo_full_count == info->philo_count)
				info->end = true;
			cur = get_elapsed_time(info);
			if (cur >= info->philo[i].last_meal_time + info->time_to_die)
			{
				info->end = true;
				print_action(info, DIED, i + 1);
				return ((void *)0);
			}
		}
	}
	return ((void *)1);
}
