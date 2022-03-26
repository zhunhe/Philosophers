/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:09:29 by juhur             #+#    #+#             */
/*   Updated: 2022/03/26 16:27:24 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

int	ft_atoi(t_info *info, const char *s)
{
	int		sign;
	int64_t	num;

	if (!*s)
	{
		info->error = true;
		return (0);
	}
	sign = 1;
	if (*s == '-')
	{
		++s;
		sign = -1;
	}
	num = 0;
	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			info->error = true;
		num = 10 * num + *(s++) - '0';
	}
	return (sign * num);
}

long long	get_cur_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (-1);
	return ((long long)t.tv_sec * MILLISEC + t.tv_usec / MILLISEC);
}

long long	get_elapsed_time(t_info *info)
{
	return (get_cur_time() - info->start_time);
}

void	print_action(t_info *info, char *action, int philo)
{
	if (!info->end)
		printf(action, get_elapsed_time(info), philo);
}
