/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:58:29 by vcarrara          #+#    #+#             */
/*   Updated: 2024/10/24 14:01:36 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

typedef struct s_philosopher
{
	pthread_t		t_id;
	int				id;
	long			meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_mtx			philo_mtx;
	t_table			*table;
}					t_philosopher;

typedef struct s_table
{
	t_philosopher	*philosophers;
	t_fork			*forks;
	long			philos_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meals_limit;
	long			sim_start;
	bool			sim_end;
	bool			all_threads_set;
	long			running_threads;
	pthread_t		monitor;
	t_mtx			table_mtx;
	t_mtx			print_mtx;
}					t_table;

typedef enum e_operations
{
	LOCK,
	UNLOCK,
	INIT,
	JOIN,
	DESTROY,
	CREATE,
	DETACH,
}					t_operations;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	FIRST_FORK,
	SECOND_FORK,
	DEAD,
}					t_status;

typedef enum e_timecode
{
	MILLISEC,
	MICROSEC,
}					t_timecode;

int						check_args(int argc, char **argv);
void					parsing(t_table *table, char **argv);
int						validation(char *argv);

void					set_long(t_mtx *mutex, long *dest, long value);
long					get_long(t_mtx *mutex, long *value);
bool					get_bool(t_mtx *mutex, bool *value);
void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					end_sim(t_table *table);

void					mutex_handler(t_mtx *mutex, t_operations op);
void					thread_handler(pthread_t *thread, void *(*foo)(void *),
							void *data, t_operations op);

void					init_table(t_table *table);

void					*one_philosopher(void *arg);
void					thinking(t_philosopher *philo, bool pre_simulation);
void					dinner_start(t_table *table);

void					*monitor(void *data);

void					add_long(t_mtx *mutex, long *value);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);
void					unsync(t_philosopher *philo);
void					wait_all_threads(t_table *table);

long					get_time(int time_code);
int						print_error(char *msg);
void					precise_usleep(long usec, t_table *table);
void					write_status(t_status status, t_philosopher *philo);
void					cleanup(t_table *table);
bool					all_threads_running(t_mtx *mutex, long *threads,
							long philo_nbr);

int						ft_isdigit(int c);
long long				ft_atol(const char *nptr);

#endif
