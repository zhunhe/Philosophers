/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:01:05 by juhur             #+#    #+#             */
/*   Updated: 2022/03/21 18:24:42 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_info	t_info;

typedef struct s_philo
{
	pthread_t	tid;
	int			order;
	int			remain_eat_count;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_info		*info;
}	t_philo;

typedef struct s_info
{
	bool		error;
	long long	start_time;
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

# define MILLISEC	1000

# define TAKEN_A_FORK	"%lld	%d	has taken a fork\n"
# define EATING			"%lld	%d	is eating\n"
# define SLEEPING		"%lld	%d	is sleeping\n"
# define THINKING		"%lld	%d	is thinking\n"

/*
** init.c
*/
t_status	init(t_info *info, int argc, char **argv);
/*
** util.c
*/
int			ft_atoi(t_info *info, const char *s);
long long	get_cur_time(void);
long long	get_elapsed_time(t_info *info);
/*
** philo.c
*/
void		*routine(void *arg);
#endif
