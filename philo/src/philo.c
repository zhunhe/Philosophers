/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:23:11 by juhur             #+#    #+#             */
/*   Updated: 2022/03/21 18:25:04 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo.h"

void	*routine(void *arg)
{
	const t_philo	*p = (t_philo *)arg;

	while (1)
	{
		if (p->order == 1)
		{
			pthread_mutex_lock(p->left_fork);
			printf(TAKEN_A_FORK, get_elapsed_time(p->info), p->order);
			pthread_mutex_lock(p->right_fork);
			printf(TAKEN_A_FORK, get_elapsed_time(p->info), p->order);
		}
		else
		{
			pthread_mutex_lock(p->right_fork);
			printf(TAKEN_A_FORK, get_elapsed_time(p->info), p->order);
			pthread_mutex_lock(p->left_fork);
			printf(TAKEN_A_FORK, get_elapsed_time(p->info), p->order);
		}
		printf(EATING, get_elapsed_time(p->info), p->order);
		usleep(p->info->time_to_eat);
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		printf(SLEEPING, get_elapsed_time(p->info), p->order);
		usleep(p->info->time_to_sleep);
		printf(THINKING, get_elapsed_time(p->info), p->order);
	}
	return ((void *)&p->order);
}
