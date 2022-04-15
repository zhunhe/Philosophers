/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:25:39 by juhur             #+#    #+#             */
/*   Updated: 2022/04/15 14:13:05 by juhur            ###   ########.fr       */
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

static void	run_simulation(t_table *table)
{
	t_philo		*p;
	int			i;
	pthread_t	thread;

	table->share.start_time = get_cur_time_in_ms();
	i = -1;
	while (++i < table->philo_count)
	{
		p = (t_philo *)&table->philo[i];
		pthread_create(&p->thread, NULL, routine, p);
	}
	pthread_create(&thread, NULL, monitor, table);
	pthread_detach(thread);
	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philo[i].thread, NULL);
}

int	main(int argc, char **argv)
{
	t_table		table;

	memset(&table, 0, sizeof(t_table));
	if (check_argc(&table, argc) != OK)
		return (1);
	if (init(&table, argc, argv) != OK)
		return (1);
	run_simulation(&table);
	destroy_mutex(&table);
	return (0);
}
