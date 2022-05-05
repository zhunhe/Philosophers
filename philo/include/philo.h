/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:01:05 by juhur             #+#    #+#             */
/*   Updated: 2022/05/05 22:56:16 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef enum e_status
{
	STATUS_OK,
	STATUS_ERROR_ARGC,
	STATUS_ERROR_INVALID_CHAR,
	STATUS_ERROR_PHILO_COUNT,
	STATUS_ERROR_MINUS,
	STATUS_ERROR_MALLOC,
	STATUS_ERROR_INIT_MUTEX,
	STATUS_ERROR_CREATE_THREAD,
	STATUS_MAX
}	t_status;

typedef struct s_share
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	int64_t		start_time;
	t_mutex		mutex_end;
	bool		end;
}				t_share;

typedef struct s_philo
{
	pthread_t	thread;
	int			order;
	t_share		*share;
	int64_t		last_meal_time;
	int			meal_count;
	t_mutex		left_fork;
	t_mutex		*right_fork;
	t_mutex		lock;
}				t_philo;

typedef struct s_table
{
	t_status	status;
	t_share		share;
	int			full_philo_count;
	int			philo_count;
	t_philo		*philo;
}				t_table;

# define TAKEN_A_FORK	"\e[1;37m%lld	%d	has taken a fork 🥢\e[0m\n"
# define EATING			"\e[1;47m\e[1;30m%lld	%d	is eating 🍝 \e[0m\e[0m\n"
# define SLEEPING		"\e[1;34m%lld	%d	is sleeping 💤\e[0m\n"
# define THINKING		"\e[1;33m%lld	%d	is thinking 🤔\e[0m\n"
# define DIED			"\e[1;40m\e[1;31m%lld	%d	is died 💀 \e[0m\e[0m\n"
# define FULL			"\e[1;35m%lld	All philosophers are full 🐷 \e[0m\n"

/*
** arg.c
*/
t_status	check_argc(t_table *table, int argc);
t_status	check_argv(t_table *table, int argc, char **argv);
/*
** init.c
*/
t_status	init(t_table *table);
/*
** philo.c
*/
void		put_down_fork(t_philo *p);
void		*philo_routine(void *arg);
/*
** time.c
*/
int64_t		get_cur_time_in_ms(void);
int64_t		get_elapsed_time_in_ms(t_share *share);
void		newsleep(int64_t wait_time);
/*
** monitor.c
*/
void		monitor_routine(t_table *table);
/*
** simulation.c
*/
void		stop_simulation(t_share *share);
t_status	run_simulation(t_table *table);
void		print_log(t_philo *p, char *action);
#endif
