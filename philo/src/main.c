/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:25:39 by juhur             #+#    #+#             */
/*   Updated: 2022/04/16 19:05:08 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <philo.h>

static int	quit_program(t_status status)
{
	const char	*error_msg[STATUS_MAX] = {
		"",
		"./philo philo_count time2die time2eat time2sleep [must_eat_count]",
		"Please input only integer number",
		"philo_count can only be a natural number!",
		"time/must_eat_count can only be natural number or 0!",
		"Failed to allocate! Insufficient memory",
		"Failed to init mutex!",
		"Failed to create thread!",
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
	if (check_argv(&table, argc, argv) != STATUS_OK)
		return (quit_program(table.status));
	if (init(&table) != STATUS_OK)
		return (quit_program(table.status));
	if (run_simulation(&table) != STATUS_OK)
		return (quit_program(table.status));
	return (0);
}
