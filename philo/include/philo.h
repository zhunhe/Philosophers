/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhur <juhur@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:01:05 by juhur             #+#    #+#             */
/*   Updated: 2022/04/14 22:19:09 by juhur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_share
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat_count;
	int64_t		start_time;
}				t_share;

typedef struct s_cs
{
	t_mutex		mutex_end;
	bool		end;
}				t_cs;

typedef struct s_philo
{
	pthread_t	thread;
	int			order;
	t_share		*share;
	t_cs		*cs;
	int64_t		last_meal_time;
	int			meal_count;
	t_mutex		*left_fork;
	t_mutex		*right_fork;
	t_mutex		fork;
	t_mutex		lock;
}				t_philo;

typedef struct s_table
{
	int			status;
	t_share		share;
	t_cs		cs;
	int			full_philo_count;
	int			philo_count;
	t_philo		*philo;
}				t_table;

typedef enum s_status
{
	OK,
	ERROR
}	t_status;

# define TAKEN_A_FORK	"\e[1;30m%lld	%d	has taken a fork\e[0m 🥢\n"
# define EATING			"\e[1;37m%lld	%d	is eating\e[0m 🍝\n"
# define SLEEPING		"\e[1;33m%lld	%d	is sleeping\e[0m 😴\n"
# define THINKING		"\e[1;34m%lld	%d	is thinking\e[0m 🤔\n"
# define DIED			"\e[1;31m%lld	%d	is died\e[0m 😵\n"
/*
** init.c
*/
t_status	init(t_table *table, int argc, char **argv);
/*
** philo.c
*/
void		create_philo(t_table *table);
void		join_philo(t_table *table);
/*
** routine.c
*/
void		put_down_fork(t_philo *p);
void		*routine(void *arg);
/*
** util.c
*/
int64_t		time_to_ms(struct timeval time);
void		print_log(t_cs *cs, char *action, int order, int64_t start_time);
bool		is_ended(t_cs *cs);
int64_t		get_cur_time_in_ms(void);
int64_t		get_elapsed_time_in_ms(t_share *share);
void		newsleep(int64_t wait_time);
/*
** monitor.c
*/
void		*monitor(void *arg);
#endif
