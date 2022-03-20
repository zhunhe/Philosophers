/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 16:15:25 by juhur             #+#    #+#             */
/*   Updated: 2022/03/20 20:59:45 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "philo.h"

static void	set_info(t_info *info, int argc, char **argv)
{
	info->philo_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->must_eat_count = ft_atoi(argv[5]);
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

static void	init_philo(t_info *info, int argc)
{
	int	i;

	if (argc != 6)
		return ;
	i = -1;
	while (++i < info->philo_count)
		info->philo[i].remain_eat_count = info->must_eat_count;
}

t_status	init(t_info *info, int argc, char **argv)
{
	set_info(info, argc, argv);
	if (check_info(info, argc) == error)
		return (error);
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_count);
	info->fork = (t_mutex *)malloc(sizeof(t_mutex) * info->philo_count);
	if (info->philo == NULL || info->fork == NULL)
		return (error);
	init_philo(info, argc);
	return (ok);
}
