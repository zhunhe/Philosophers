/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:42:38 by juhur             #+#    #+#             */
/*   Updated: 2022/04/14 14:16:56 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <philo.h>

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
			table->status = ERROR;
			break ;
		}
		num = num * 10 + *(str++) - '0';
	}
	return (sign * num);
}

static t_status	set_table_data(t_table *table, int argc, char **argv)
{
	table->philo_count = _atoi(table, argv[1]);
	table->share.time_to_die = _atoi(table, argv[2]);
	table->share.time_to_eat = _atoi(table, argv[3]);
	table->share.time_to_sleep = _atoi(table, argv[4]);
	table->share.must_eat_count = -1;
	if (argc == 6)
		table->share.must_eat_count = _atoi(table, argv[5]);
	return (table->status);
}

static t_status	check_table_data(t_table *table, int argc)
{
	if (table->philo_count < 1)
		table->status = ERROR;
	if (table->share.time_to_die < 0)
		table->status = ERROR;
	if (table->share.time_to_eat < 0)
		table->status = ERROR;
	if (table->share.time_to_sleep < 0)
		table->status = ERROR;
	if (argc == 6 && table->share.must_eat_count < 0)
		table->status = ERROR;
	return (table->status);
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
		pthread_mutex_init(&p->fork, NULL);
		pthread_mutex_init(&p->lock, NULL);
	}
}

t_status	init(t_table *table, int argc, char **argv)
{
	if (set_table_data(table, argc, argv) != OK)
		return (table->status);
	if (check_table_data(table, argc) != OK)
		return (table->status);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (table->philo == NULL)
		return (table->status = ERROR);
	pthread_mutex_init(&table->cs.mutex_end, NULL);
	init_philo(table);
	return (OK);
}
