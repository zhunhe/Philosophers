/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:25:39 by juhur             #+#    #+#             */
/*   Updated: 2022/04/16 18:45:20 by juhur            ###   ########.fr       */
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

int	_atoi(t_table *table, char *str)
{
	int		sign;
	int64_t	num;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	num = 0;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
		{
			table->status = STATUS_ERROR_ARGV;
			break ;
		}
		num = num * 10 + *(str++) - '0';
	}
	return (sign * num);
}

static t_status	check_argv(t_table *table, int argc, char **argv)
{
	table->philo_count = _atoi(table, argv[1]);
	table->share.time_to_die = _atoi(table, argv[2]);
	table->share.time_to_eat = _atoi(table, argv[3]);
	table->share.time_to_sleep = _atoi(table, argv[4]);
	table->share.must_eat_count = -1;
	if (argc == 6)
		table->share.must_eat_count = _atoi(table, argv[5]);
	if (table->status != STATUS_OK)
		return (table->status);
	if (table->philo_count < 1)
		table->status = STATUS_ERROR_ARGV;
	if (table->share.time_to_die < 0)
		table->status = STATUS_ERROR_ARGV;
	if (table->share.time_to_eat < 0)
		table->status = STATUS_ERROR_ARGV;
	if (table->share.time_to_sleep < 0)
		table->status = STATUS_ERROR_ARGV;
	if (argc == 6 && table->share.must_eat_count < 0)
		table->status = STATUS_ERROR_ARGV;
	return (table->status);
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
