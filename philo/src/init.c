/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:15:25 by juhur             #+#    #+#             */
/*   Updated: 2022/03/21 16:53:59 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include <stdio.h>

static void	set_info(t_info *info, int argc, char **argv)
{
	info->philo_count = ft_atoi(info, argv[1]);
	info->time_to_die = ft_atoi(info, argv[2]);
	info->time_to_eat = ft_atoi(info, argv[3]);
	info->time_to_sleep = ft_atoi(info, argv[4]);
	if (argc == 6)
		info->must_eat_count = ft_atoi(info, argv[5]);
}

static t_status	check_info(t_info *info, int argc)
{
	if (info->philo_count < 1)
		return (error);
	if (info->time_to_die < 0)
		return (error);
	if (info->time_to_eat < 0)
		return (error);
	if (info->time_to_sleep < 0)
		return (error);
	if (argc == 6 && info->must_eat_count < 0)
		return (error);
	return (ok);
}

void	*routine(void *arg)
{
	const t_philo	*philo = (t_philo *)arg;

	while (1)
	{
		if (philo->order == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			printf("time	%d	has taken a fork\n", philo->order);
			pthread_mutex_lock(philo->right_fork);
			printf("time	%d	has taken a fork\n", philo->order);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			printf("time	%d	has taken a fork\n", philo->order);
			pthread_mutex_lock(philo->left_fork);
			printf("time	%d	has taken a fork\n", philo->order);
		}
		printf("time	%d	is eating\n", philo->order);
		usleep(1000 * philo->info->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("time	%d	is sleeping\n", philo->order);
		usleep(1000 * philo->info->time_to_sleep);
		printf("time	%d	is thinking\n", philo->order);
	}
	return ((void *)&philo->order);
}

static void	init_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_count)
	{
		info->philo[i].order = i + 1;
		info->philo[i].remain_eat_count = info->must_eat_count;
		info->philo[i].left_fork = &info->fork[i];
		info->philo[i].right_fork = &info->fork[(i + 1) % info->philo_count];
		info->philo[i].info = info;
		pthread_create(&info->philo[i].tid, NULL, routine, (void *)&info->philo[i]);
	}
}

t_status	init(t_info *info, int argc, char **argv)
{
	void	*ret;
	
	set_info(info, argc, argv);
	if (info->error)
		return (error);
	if (check_info(info, argc) == error)
		return (error);
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_count);
	info->fork = (t_mutex *)malloc(sizeof(t_mutex) * info->philo_count);
	if (info->philo == NULL || info->fork == NULL)
		return (error);
	init_philo(info);
	for (int i = 0; i < info->philo_count; i++)
		pthread_mutex_init(&info->fork[i], NULL);
	for (int i = 0; i < info->philo_count; i++)
		pthread_join(info->philo[i].tid, &ret);
	for (int i = 0; i < info->philo_count; i++)
		pthread_mutex_destroy(&info->fork[i]);
	return (ok);
}
