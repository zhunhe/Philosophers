/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:58:16 by juhur             #+#    #+#             */
/*   Updated: 2022/04/14 14:05:27 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <philo.h>

int64_t	time_to_ms(struct timeval time)
{
	return ((int64_t)time.tv_sec * 1000 + time.tv_usec / 1000);
}

bool	is_ended(t_cs *cs)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&cs->mutex_end);
	result = cs->end;
	pthread_mutex_unlock(&cs->mutex_end);
	return (result);
}

void	print_log(t_cs *cs, char *action, int order, int64_t start_time)
{
	pthread_mutex_lock(&cs->mutex_end);
	if (!cs->end)
		printf(action, get_cur_time_in_ms() - start_time, order);
	pthread_mutex_unlock(&cs->mutex_end);
}

int64_t	get_cur_time_in_ms(void)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (time_to_ms(cur));
}

void	newsleep(int64_t wait_time)
{
	int64_t			start_time;

	start_time = get_cur_time_in_ms();
	while (get_cur_time_in_ms() - start_time < wait_time)
		usleep(100);
}
