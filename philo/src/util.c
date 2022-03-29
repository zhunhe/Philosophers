/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:09:29 by juhur             #+#    #+#             */
/*   Updated: 2022/03/29 10:37:50 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	new_sleep(long long sleep_time)
{
	const long long	start_time = get_cur_time();
	long long		cur_time;

	cur_time = get_cur_time();
	while (cur_time < start_time + sleep_time)
	{
		usleep(42);
		cur_time = get_cur_time();
	}
}
