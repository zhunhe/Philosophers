/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:25:39 by juhur             #+#    #+#             */
/*   Updated: 2022/04/14 11:15:56 by juhur            ###   ########.fr       */
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

	i = -1;
	while (++i < table->philo_count)
		pthread_mutex_destroy(&table->philo[i].fork);
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
	pthread_create(&thread, NULL, monitor, &table);
	pthread_detach(thread);
	create_philo(&table);
	join_philo(&table);
	destroy_mutex(&table);
	return (0);
}
