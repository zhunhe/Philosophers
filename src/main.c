/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:59:45 by juhur             #+#    #+#             */
/*   Updated: 2022/03/08 16:25:23 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

static t_status	init(t_info *info, int argc, char **argv)
{
	int	i;
	int	must_eat_count;

	info->philo_count = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->philo_count < 2 || info->time_to_die < 0 \
		|| info->time_to_eat < 0 || info->time_to_sleep < 0)
		return (error);
	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->philo_count);
	if (info->philo == NULL)
		return (error);
	if (argc == 6)
	{
		must_eat_count = ft_atoi(argv[5]);
		if (must_eat_count < 0)
		{
			free(info->philo);
			return (error);
		}
		i = -1;
		while (++i < info->philo_count)
		{
			info->philo[i].tid = 0;
			info->philo[i].remain_eat_count = must_eat_count;
		}
	}
	return (ok);
}

int	main(int argc, char **argv)
{
	t_info		info;
	t_status	ret;

	if (argc != 5 && argc != 6)
		return (error);
	ret = init(&info, argc, argv);
	if (ret == error)
		return (error);
	return (0);
}
