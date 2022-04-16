/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 14:36:42 by juhur             #+#    #+#             */
/*   Updated: 2022/04/16 14:36:52 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_status	run_simulation(t_table *table)
{
	t_philo		*p;
	int			i;
	pthread_t	thread;

	table->share.start_time = get_cur_time_in_ms();
	i = -1;
	while (++i < table->philo_count)
	{
		p = (t_philo *)&table->philo[i];
		if (pthread_create(&p->thread, NULL, routine, p))
		{
			pthread_mutex_lock(&table->cs.mutex_end);
			table->cs.end = true;
			pthread_mutex_unlock(&table->cs.mutex_end);
			table->status = STATUS_ERROR_CREATE_THREAD;
		}
	}
	if (pthread_create(&thread, NULL, monitor, table))
	{
		pthread_mutex_lock(&table->cs.mutex_end);
		table->cs.end = true;
		pthread_mutex_unlock(&table->cs.mutex_end);
		table->status = STATUS_ERROR_CREATE_THREAD;
	}
	else
		pthread_detach(thread);
	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philo[i].thread, NULL);
	return (table->status);
}
