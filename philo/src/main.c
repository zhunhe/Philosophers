/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 13:59:45 by juhur             #+#    #+#             */
/*   Updated: 2022/03/27 21:37:50 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include <string.h>
#include <stdlib.h>
#include "philo.h"

int	main(int argc, char **argv)
{
	t_info		info;
	int			i;

	if (argc != 5 && argc != 6)
		return (EX_USAGE);
	memset(&info, 0, sizeof(t_info));
	if (init(&info, argc, argv) == ok)
	{
		while (!info.end)
			;
	}
	i = -1;
	while (++i < info.philo_count)
		pthread_mutex_destroy(&info.fork[i]);
	if (info.philo != NULL)
		free(info.philo);
	if (info.fork != NULL)
		free(info.fork);
	return (EXIT_SUCCESS);
}
