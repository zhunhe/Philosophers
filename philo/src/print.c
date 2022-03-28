/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:48:04 by juhur             #+#    #+#             */
/*   Updated: 2022/03/28 14:55:17 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

void	print_action(t_info *info, char *action, int philo)
{
	if (!info->end || !ft_strcmp(action, DIED))
		printf(action, get_elapsed_time(info), philo);
}
