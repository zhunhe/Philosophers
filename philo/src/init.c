/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:42:38 by juhur             #+#    #+#             */
/*   Updated: 2022/04/15 21:48:42 by juhur            ###   ########.fr       */
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
			table->status = STATUS_ERROR_ARGV;
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
		return (STATUS_ERROR_ARGV);
	if (table->share.time_to_die < 0)
		return (STATUS_ERROR_ARGV);
	if (table->share.time_to_eat < 0)
		return (STATUS_ERROR_ARGV);
	if (table->share.time_to_sleep < 0)
		return (STATUS_ERROR_ARGV);
	if (argc == 6 && table->share.must_eat_count < 0)
		return (STATUS_ERROR_ARGV);
	return (STATUS_OK);
}

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

t_status	init(t_table *table, int argc, char **argv)
{
	if (set_table_data(table, argc, argv) != STATUS_OK)
		return (table->status);
	if (check_table_data(table, argc) != STATUS_OK)
		return (table->status = STATUS_ERROR_ARGV);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (table->philo == NULL)
		return (table->status = STATUS_ERROR_MALLOC);
	if (init_mutex(table) != STATUS_OK)
		return (table->status = STATUS_ERROR_INIT_MUTEX);
	init_philo(table);
	return (STATUS_OK);
}
