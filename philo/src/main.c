/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:25:39 by juhur             #+#    #+#             */
/*   Updated: 2022/04/16 16:25:07 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <philo.h>

static t_status	check_argc(t_table *table, int argc)
{
	if (argc != 5 && argc != 6)
		table->status = STATUS_ERROR_ARGC;
	return (table->status);
}

static void	destory_free(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->cs.mutex_end);
	i = -1;
	while (++i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philo[i].fork);
		pthread_mutex_destroy(&table->philo[i].lock);
	}
	free(table->philo);
}

static int	quit_program(t_status status)
{
	const char	*error_msg[STATUS_MAX] = {
		"",
		"ERROR! ./philo philo_count time_to_die time_to_eat_ time_to_sleep \
		[must_eat_count]",
		"ERROR! Input only positive number",
		"ERROR! Insufficient memory",
		"ERROR! Failed to init mutex",
		"ERROR! Failed to create thread",
	};

	printf("%s\n", error_msg[status]);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table		table;

	memset(&table, 0, sizeof(t_table));
	if (check_argc(&table, argc) != STATUS_OK)
		return (quit_program(table.status));
	if (init(&table, argc, argv) != STATUS_OK)
		return (quit_program(table.status));
	if (run_simulation(&table) != STATUS_OK)
		return (quit_program(table.status));
	destory_free(&table);
	return (0);
}
