/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:01:05 by juhur             #+#    #+#             */
/*   Updated: 2022/03/20 21:03:28 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	pthread_t	tid;
	int			remain_eat_count;
}	t_philo;

typedef struct s_info
{
	bool		error;
	int			philo_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	t_philo		*philo;
	t_mutex		*fork;
}	t_info;

typedef enum e_status
{
	ok = 0,
	error,
	max
}	t_status;

/*
** init.c
*/
t_status	init(t_info *info, int argc, char **argv);
/*
** util.c
*/
int			ft_atoi(t_info *info, const char *s);
#endif
