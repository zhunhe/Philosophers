/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:37:01 by juhur             #+#    #+#             */
/*   Updated: 2022/05/05 22:54:51 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philo.h>

static int	end_simulation(t_share *share, bool died, t_philo *p)
{
	stop_simulation(share);
	if (died)
	{
		printf(DIED, get_elapsed_time_in_ms(share), p->order);
		put_down_fork(p);
	}
	else
		printf(FULL, get_elapsed_time_in_ms(share));
	return (1);
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
		if (get_elapsed_time_in_ms(s) >= s->time_to_die + p->last_meal_time)
			is_philo_died = true;
		pthread_mutex_unlock(&p->lock);
		if (is_philo_died)
			break ;
	}
	if (is_philo_died || all_philo_full)
		return (end_simulation(&table->share, is_philo_died, p));
	return (0);
}

void	monitor_routine(t_table *table)
{
	while (!check_simulation(table))
		usleep(1000);
}
