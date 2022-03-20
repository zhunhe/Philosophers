/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:09:29 by juhur             #+#    #+#             */
/*   Updated: 2022/03/20 21:16:35 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
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
