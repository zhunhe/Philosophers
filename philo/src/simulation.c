/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 14:36:42 by juhur             #+#    #+#             */
/*   Updated: 2022/04/18 16:54:17 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <philo.h>

void	stop_simulation(t_cs *cs)
{
	pthread_mutex_lock(&cs->mutex_end);
	cs->end = true;
	pthread_mutex_unlock(&cs->mutex_end);
}

static void	destroy_free(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->cs.mutex_end);
	i = -1;
	while (++i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philo[i].fork);
		pthread_mutex_destroy(&table->philo[i].lock);
	}
	if (table->philo)
	{
		free(table->philo);
		table->philo = NULL;
	}
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
		if (pthread_create(&p->thread, NULL, philo_routine, p))
		{
			stop_simulation(&table->cs);
			table->status = STATUS_ERROR_CREATE_THREAD;
			break ;
		}
	}
	if (table->status == STATUS_OK)
		table->status = create_monitor(table);
	while (i--)
		pthread_join(table->philo[i].thread, NULL);
	destroy_free(table);
	return (table->status);
}

bool	is_ended(t_cs *cs)
{
	bool	result;

	pthread_mutex_lock(&cs->mutex_end);
	result = cs->end;
	pthread_mutex_unlock(&cs->mutex_end);
	return (result);
}

void	print_log(t_philo *p, char *action)
{
	pthread_mutex_lock(&p->cs->mutex_end);
	if (!p->cs->end)
		printf(action, get_elapsed_time_in_ms(p->share), p->order);
	pthread_mutex_unlock(&p->cs->mutex_end);
}
