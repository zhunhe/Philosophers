/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:32:05 by juhur             #+#    #+#             */
/*   Updated: 2022/04/17 23:55:57 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philo.h>

static void	take_fork(t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	print_log(p, TAKEN_A_FORK);
	pthread_mutex_lock(p->right_fork);
	print_log(p, TAKEN_A_FORK);
}

void	put_down_fork(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

static void	eating(t_philo *p)
{
	pthread_mutex_lock(&p->lock);
	print_log(p, EATING);
	p->last_meal_time = get_elapsed_time_in_ms(p->share);
	++p->meal_count;
	pthread_mutex_unlock(&p->lock);
	newsleep(p->share->time_to_eat);
	put_down_fork(p);
}

static void	sleeping_thinking(t_philo *p)
{
	print_log(p, SLEEPING);
	newsleep(p->share->time_to_sleep);
	print_log(p, THINKING);
}

void	*philo_routine(void *arg)
{
	t_philo		*p;

	p = (t_philo *)arg;
	if (p->order & 1)
		usleep(p->share->time_to_eat * 1000);
	while (!is_ended(p->cs))
	{
		take_fork(p);
		eating(p);
		sleeping_thinking(p);
	}
	return (NULL);
}
