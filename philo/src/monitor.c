/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:37:01 by juhur             #+#    #+#             */
/*   Updated: 2022/04/15 14:05:14 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philo.h>

static void	handle_someone_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->cs->mutex_end);
	printf(DIED, get_cur_time_in_ms() - philo->share->start_time, philo->order);
	philo->cs->end = 1;
	put_down_fork(philo);
	pthread_mutex_unlock(&philo->cs->mutex_end);
}

void	stop_simulation(t_table *table)
{
	pthread_mutex_lock(&table->cs.mutex_end);
	table->cs.end = 1;
	pthread_mutex_unlock(&table->cs.mutex_end);
}

static void	handle_everyone_full(t_table *table)
{
	stop_simulation(table);
}

int	is_monitor_end(t_table *table)
{
	int	i;
	int	everyone_full;
	int	someone_dead;

	everyone_full = (table->share.must_eat_count != -1);
	someone_dead = 0;
	i = -1;
	while (++i < table->philo_count)
	{
		pthread_mutex_lock(&table->philo[i].lock);
		everyone_full &= (table->share.must_eat_count <= table->philo[i].meal_count);
		someone_dead = (get_elapsed_time_in_ms(&table->share) - table->philo[i].last_meal_time > table->share.time_to_die);
		pthread_mutex_unlock(&table->philo[i].lock);
		if (someone_dead)
			break ;
	}
	if (someone_dead)
		handle_someone_dead(table->philo + i);
	else if (everyone_full)
		handle_everyone_full(table);
	return (everyone_full || someone_dead);
}

void	*monitor(void *arg)
{
	t_table	*t;

	t = (t_table *)arg;
	while (!is_monitor_end(t))
		usleep(1000);
	return (NULL);
}
