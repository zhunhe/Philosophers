/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:09:29 by juhur             #+#    #+#             */
/*   Updated: 2022/03/08 16:28:16 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int	ft_atoi(const char *s)
{
	int		sign;
	int64_t	num;

	if (!*s)
		return (0);
	sign = 1;
	if (*s == '-')
	{
		++s;
		sign = -1;
	}
	num = 0;
	while (*s != '\0')
		num *= 10 + *(s++) - '0';
	return (sign * num);
}