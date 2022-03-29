/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:23:11 by juhur             #+#    #+#             */
/*   Updated: 2022/03/29 17:26:05 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_action(p->info, TAKEN_A_FORK, p->order);
	pthread_mutex_lock(p->right_fork);
	print_action(p->info, TAKEN_A_FORK, p->order);
	p->last_meal_time = get_elapsed_time(p->info);
	print_action(p->info, EATING, p->order);
	new_sleep(p->info->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	if (p->remain_eat_count > 0)
		if (--p->remain_eat_count == 0)
			++p->info->philo_full_count;
}

static void	sleeping(t_philo *p)
{
	print_action(p->info, SLEEPING, p->order);
	new_sleep(p->info->time_to_sleep);
}

static void	thinking(t_philo *p)
{
	print_action(p->info, THINKING, p->order);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->order % 2 == 0)
		new_sleep(p->info->time_to_eat);
	while (!p->info->end && p->remain_eat_count)
	{
		eating(p);
		sleeping(p);
		thinking(p);
	}
	return ((void *)&p->order);
}
