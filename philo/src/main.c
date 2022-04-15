/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:25:39 by juhur             #+#    #+#             */
/*   Updated: 2022/04/15 14:03:22 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <philo.h>

static t_status	check_argc(t_table *table, int argc)
{
	if (argc != 5 && argc != 6)
		table->status = ERROR;
	return (table->status);
}

static void	destroy_mutex(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->cs.mutex_end);
	i = -1;
	while (++i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philo[i].fork);
		pthread_mutex_destroy(&table->philo[i].lock);
	}
}

static void	join_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philo[i].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_table		table;
	pthread_t	thread;

	memset(&table, 0, sizeof(t_table));
	if (check_argc(&table, argc) != OK)
		return (1);
	if (init(&table, argc, argv) != OK)
		return (1);
	create_philo(&table);
	pthread_create(&thread, NULL, monitor, &table);
	pthread_detach(thread);
	join_philo(&table);
	destroy_mutex(&table);
	return (0);
}
