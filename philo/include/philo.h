/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:01:05 by juhur             #+#    #+#             */
/*   Updated: 2022/03/27 19:23:17 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_info	t_info;

typedef enum s_state
{
	STATE_PHILO_READY,
	STATE_PHILO_ATE,
	STATE_PHILO_WAKE_UP,
	STATE_PHILO_THOUGHT,
	STATE_PHILO_DEAD,
	STATE_PHILO_FULL
}	t_state;

typedef struct s_philo
{
	pthread_t	tid;
	int			order;
	t_state		state;
	int			remain_eat_count;
	long long	last_meal_time;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_info		*info;
}	t_philo;

typedef struct s_info
{
	bool		error;
	bool		end;
	long long	start_time;
	int			philo_count;
	int			philo_full_count;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	t_philo		*philo;
	t_mutex		*fork;
	pthread_t	monitor;
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
# define DIED			"%lld	%d	is died\n"

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
void		print_action(t_info *info, char *action, int philo);
void		new_sleep(long long sleep_time);
/*
** philo.c
*/
void		*routine(void *arg);
/*
** monitor.c
*/
void		*check_alive(void *arg);
#endif
