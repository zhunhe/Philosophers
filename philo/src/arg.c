/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 18:54:22 by juhur             #+#    #+#             */
/*   Updated: 2022/04/16 19:09:59 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_status	check_argc(t_table *table, int argc)
{
	if (argc != 5 && argc != 6)
		table->status = STATUS_ERROR_ARGC;
	return (table->status);
}

static int	_atoi(t_table *table, char *str)
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
			table->status = STATUS_ERROR_INVALID_CHAR;
			break ;
		}
		num = num * 10 + *(str++) - '0';
	}
	return (sign * num);
}

static t_status	check_argv_range(t_table *table, int argc)
{
	if (table->philo_count < 1)
		return (table->status = STATUS_ERROR_PHILO_COUNT);
	if (table->share.time_to_die < 0)
		return (table->status = STATUS_ERROR_MINUS);
	if (table->share.time_to_eat < 0)
		return (table->status = STATUS_ERROR_MINUS);
	if (table->share.time_to_sleep < 0)
		return (table->status = STATUS_ERROR_MINUS);
	if (argc == 6 && table->share.must_eat_count < 0)
		return (table->status = STATUS_ERROR_MINUS);
	return (table->status);
}

t_status	check_argv(t_table *table, int argc, char **argv)
{
	table->philo_count = _atoi(table, argv[1]);
	table->share.time_to_die = _atoi(table, argv[2]);
	table->share.time_to_eat = _atoi(table, argv[3]);
	table->share.time_to_sleep = _atoi(table, argv[4]);
	table->share.must_eat_count = -1;
	if (argc == 6)
		table->share.must_eat_count = _atoi(table, argv[5]);
	return (check_argv_range(table, argc));
}
