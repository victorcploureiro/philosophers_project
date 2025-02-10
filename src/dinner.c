/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:24:41 by vcarrara          #+#    #+#             */
/*   Updated: 2024/10/30 14:38:36 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philosopher(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISEC));
	add_long(&philo->table->table_mtx,
		&philo->table->running_threads);
	write_status(FIRST_FORK, philo);
	while (!end_sim(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}

void	thinking(t_philosopher *philo, bool pre_sim)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_sim)
		write_status(THINKING, philo);
	if (philo->table->philos_count % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

static void	eating(t_philosopher *philo)
{
	mutex_handler(&philo->left_fork->fork, LOCK);
	write_status(FIRST_FORK, philo);
	mutex_handler(&philo->right_fork->fork, LOCK);
	write_status(SECOND_FORK, philo);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISEC));
	philo->meals_counter++;
	write_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->meals_limit > 0
		&& philo->meals_counter == philo->table->meals_limit)
		set_bool(&philo->philo_mtx, &philo->full, true);
	mutex_handler(&philo->left_fork->fork, UNLOCK);
	mutex_handler(&philo->right_fork->fork, UNLOCK);
}

static void	*dinner_simulation(void *data)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISEC));
	add_long(&philo->table->table_mtx,
		&philo->table->running_threads);
	unsync(philo);
	while (!end_sim(philo->table))
	{
		if (get_bool(&philo->philo_mtx, &philo->full))
			break ;
		eating(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals_limit == 0)
		return ;
	else if (table->philos_count == 1)
		thread_handler(&table->philosophers[0].t_id, one_philosopher,
			&table->philosophers[0], CREATE);
	else
		while (table->philos_count > ++i)
			thread_handler(&table->philosophers[i].t_id, dinner_simulation,
				&table->philosophers[i], CREATE);
	thread_handler(&table->monitor, monitor, table, CREATE);
	table->sim_start = get_time(MILLISEC);
	set_bool(&table->table_mtx, &table->all_threads_set, true);
	i = -1;
	while (table->philos_count > ++i)
		thread_handler(&table->philosophers[i].t_id, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->sim_end, true);
	thread_handler(&table->monitor, NULL, NULL, JOIN);
}
