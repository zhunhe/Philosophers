/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:32:05 by juhur             #+#    #+#             */
/*   Updated: 2022/04/15 11:35:03 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philo.h>

static bool	take_fork(t_philo *p)
{
	if (p->order & 1)
	{
		pthread_mutex_lock(p->left_fork);
		print_log(p->cs, TAKEN_A_FORK, p->order, p->share->start_time);
		pthread_mutex_lock(p->right_fork);
		print_log(p->cs, TAKEN_A_FORK, p->order, p->share->start_time);
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		print_log(p->cs, TAKEN_A_FORK, p->order, p->share->start_time);
		pthread_mutex_lock(p->left_fork);
		print_log(p->cs, TAKEN_A_FORK, p->order, p->share->start_time);
	}
	return (is_ended(p->cs));
}

void	put_down_fork(t_philo *p)
{
	if (p->order & 1)
	{
		pthread_mutex_unlock(p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
	else
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(p->left_fork);
	}
}

static bool	eating(t_philo *p)
{
	pthread_mutex_lock(&p->lock);
	print_log(p->cs, EATING, p->order, p->share->start_time);
	p->last_meal_time = get_elapsed_time_in_ms(p->share);
	++p->meal_count;
	pthread_mutex_unlock(&p->lock);
	newsleep(p->share->time_to_eat);
	put_down_fork(p);
	return (is_ended(p->cs));
}

static bool	sleeping(t_philo *p)
{
	print_log(p->cs, SLEEPING, p->order, p->share->start_time);
	newsleep(p->share->time_to_sleep);
	return (is_ended(p->cs));
}

static bool	thinking(t_philo *p)
{
	print_log(p->cs, THINKING, p->order, p->share->start_time);
	return (is_ended(p->cs));
}

void	*routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	if (p->order & 1)
		usleep(p->share->time_to_eat * 1000);
	while (!is_ended(p->cs))
	{
		take_fork(p);
		eating(p);
		sleeping(p);
		thinking(p);
	}
	return (NULL);
}
