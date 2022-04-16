/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 14:36:42 by juhur             #+#    #+#             */
/*   Updated: 2022/04/16 15:00:25 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	stop_simulation(t_cs *cs)
{
	pthread_mutex_lock(&cs->mutex_end);
	cs->end = true;
	pthread_mutex_unlock(&cs->mutex_end);
}

t_status	run_simulation(t_table *table)
{
	t_philo		*p;
	int			i;

	table->share.start_time = get_cur_time_in_ms();
	i = -1;
	while (++i < table->philo_count)
	{
		p = (t_philo *)&table->philo[i];
		if (pthread_create(&p->thread, NULL, routine, p))
		{
			stop_simulation(&table->cs);
			table->status = STATUS_ERROR_CREATE_THREAD;
		}
	}
	if (pthread_create(&table->monitor, NULL, monitor, table))
	{
		stop_simulation(&table->cs);
		table->status = STATUS_ERROR_CREATE_THREAD;
	}
	else
		pthread_detach(table->monitor);
	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philo[i].thread, NULL);
	return (table->status);
}

bool	is_ended(t_cs *cs)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&cs->mutex_end);
	result = cs->end;
	pthread_mutex_unlock(&cs->mutex_end);
	return (result);
}
