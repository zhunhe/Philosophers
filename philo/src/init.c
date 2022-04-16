/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:42:38 by juhur             #+#    #+#             */
/*   Updated: 2022/04/16 18:13:02 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <philo.h>

static t_status	init_philo_mutex(t_philo *p)
{
	if (pthread_mutex_init(&p->fork, NULL))
		return (STATUS_ERROR_INIT_MUTEX);
	if (pthread_mutex_init(&p->lock, NULL))
	{
		pthread_mutex_destroy(&p->fork);
		return (STATUS_ERROR_INIT_MUTEX);
	}
	return (STATUS_OK);
}

static t_status	init_mutex(t_table *table)
{
	int		i;

	if (pthread_mutex_init(&table->cs.mutex_end, NULL))
		return (STATUS_ERROR_INIT_MUTEX);
	i = -1;
	while (++i < table->philo_count)
	{
		if (init_philo_mutex(&table->philo[i]) != STATUS_OK)
		{
			pthread_mutex_destroy(&table->cs.mutex_end);
			while (i--)
			{
				pthread_mutex_destroy(&table->philo[i].fork);
				pthread_mutex_destroy(&table->philo[i].lock);
			}
			return (STATUS_ERROR_INIT_MUTEX);
		}
	}
	return (STATUS_OK);
}

static void	init_philo(t_table *table)
{
	t_philo	*p;
	int		i;

	i = -1;
	while (++i < table->philo_count)
	{
		p = (t_philo *)&table->philo[i];
		p->order = i + 1;
		p->left_fork = &table->philo[i].fork;
		p->right_fork = &table->philo[(i + 1) % table->philo_count].fork;
		p->cs = &table->cs;
		p->share = &table->share;
	}
}

t_status	init(t_table *table)
{
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (table->philo == NULL)
		return (table->status = STATUS_ERROR_MALLOC);
	if (init_mutex(table) != STATUS_OK)
		return (table->status = STATUS_ERROR_INIT_MUTEX);
	init_philo(table);
	return (STATUS_OK);
}
