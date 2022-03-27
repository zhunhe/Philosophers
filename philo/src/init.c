/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:15:25 by juhur             #+#    #+#             */
/*   Updated: 2022/03/27 21:50:57 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

static void	set_info(t_info *info, int argc, char **argv)
{
	info->philo_count = ft_atoi(info, argv[1]);
	info->time_to_die = ft_atoi(info, argv[2]);
	info->time_to_eat = ft_atoi(info, argv[3]);
	info->time_to_sleep = ft_atoi(info, argv[4]);
	info->must_eat_count = -1;
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

static void	init_philo(t_info *info)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < info->philo_count)
	{
		philo = &info->philo[i];
		philo->order = i + 1;
		philo->state = STATE_PHILO_HUNGRY;
		philo->remain_eat_count = info->must_eat_count;
		philo->left_fork = &info->fork[i];
		philo->right_fork = &info->fork[(i + 1) % info->philo_count];
		philo->info = info;
		pthread_create(&philo->tid, NULL, routine, (void *)philo);
		pthread_detach(philo->tid);
	}
}

t_status	init(t_info *info, int argc, char **argv)
{
	int	i;

	set_info(info, argc, argv);
	if (info->error)
		return (error);
	if (check_info(info, argc) == error)
		return (error);
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_count);
	info->fork = (t_mutex *)malloc(sizeof(t_mutex) * info->philo_count);
	if (info->philo == NULL || info->fork == NULL)
		return (error);
	info->start_time = get_cur_time();
	i = -1;
	while (++i < info->philo_count)
		pthread_mutex_init(&info->fork[i], NULL);
	pthread_create(&info->monitor, NULL, check_alive, (void *)info);
	pthread_detach(info->monitor);
	init_philo(info);
	return (ok);
}
