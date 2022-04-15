/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:24:44 by juhur             #+#    #+#             */
/*   Updated: 2022/04/15 11:48:16 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	create_philo(t_table *table)
{
	t_philo	*p;
	int		i;

	table->share.start_time = get_cur_time_in_ms();
	i = -1;
	while (++i < table->philo_count)
	{
		p = (t_philo *)&table->philo[i];
		pthread_create(&p->thread, NULL, routine, p);
	}
}

void	join_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philo[i].thread, NULL);
}
