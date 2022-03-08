/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:01:05 by juhur             #+#    #+#             */
/*   Updated: 2022/03/08 16:28:41 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	pthread_t	tid;
	int			remain_eat_count;
}	t_philo;

typedef struct s_info
{
	int		philo_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	t_philo	*philo;
}	t_info;

typedef enum e_status
{
	ok = 0,
	error,
	max
}	t_status;

/*
** util.c
*/
int		ft_atoi(const char *s);
#endif
