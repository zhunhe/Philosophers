/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:37:01 by juhur             #+#    #+#             */
/*   Updated: 2022/04/15 14:47:44 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philo.h>

static void	end_simulation(t_philo *p, bool full, bool died)
{
	if (!full && !died)
		return ;
	pthread_mutex_lock(&p->cs->mutex_end);
	if (died)
	{
		printf(DIED, get_elapsed_time_in_ms(p->share), p->order);
		put_down_fork(p);
	}
	p->cs->end = 1;
	pthread_mutex_unlock(&p->cs->mutex_end);
}

static bool	check_simulation(t_table *table)
{
	int		i;
	bool	all_philo_full;
	bool	is_philo_died;
	t_share	*s;
	t_philo	*p;

	all_philo_full = (table->share.must_eat_count != -1);
	is_philo_died = false;
	i = -1;
	while (++i < table->philo_count)
	{
		p = &table->philo[i];
		s = &table->share;
		pthread_mutex_lock(&p->lock);
		all_philo_full &= (s->must_eat_count <= p->meal_count);
		is_philo_died = (get_elapsed_time_in_ms(s) - p->last_meal_time > s->time_to_die);
		pthread_mutex_unlock(&p->lock);
		if (is_philo_died)
			break ;
	}
	if (all_philo_full || is_philo_died)
	{
		end_simulation(&table->philo[i], all_philo_full, is_philo_died);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*t;

	t = (t_table *)arg;
	while (!check_simulation(t))
		usleep(1000);
	return (NULL);
}
