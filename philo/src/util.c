/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:58:16 by juhur             #+#    #+#             */
/*   Updated: 2022/04/16 15:11:20 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <philo.h>

int64_t	time_to_ms(struct timeval time)
{
	return ((int64_t)time.tv_sec * 1000 + time.tv_usec / 1000);
}

int64_t	get_cur_time_in_ms(void)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (time_to_ms(cur));
}

int64_t	get_elapsed_time_in_ms(t_share *share)
{
	return (get_cur_time_in_ms() - share->start_time);
}

void	newsleep(int64_t wait_time)
{
	int64_t	end_time;

	end_time = get_cur_time_in_ms() + wait_time;
	while (get_cur_time_in_ms() < end_time)
		usleep(100);
}
