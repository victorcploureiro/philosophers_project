/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:31:18 by vcarrara          #+#    #+#             */
/*   Updated: 2024/12/11 11:40:16 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	dead(t_philosopher *philo)
{
	long	elapsed;
	long	time_to_die;

	if (get_bool(&philo->philo_mtx, &philo->full))
		return (false);
	elapsed = get_time(MILLISEC)
		- get_long(&philo->philo_mtx, &philo->last_meal_time);
	time_to_die = philo->table->time_to_die / 1e3;
	if (elapsed > time_to_die)
		return (true);
	return (false);
}

void	*monitor(void *data)
{
	int			i;
	t_table		*table;

	table = (t_table *)data;
	while (!all_threads_running(&table->table_mtx, &table->running_threads,
			table->philos_count))
		;
	while (!end_sim(table))
	{
		i = -1;
		while ((++i < table->philos_count) && !end_sim(table))
		{
			if (dead(table->philosophers + i))
			{
				set_bool(&table->table_mtx, &table->sim_end, true);
				pthread_mutex_lock(&table->print_mtx);
				printf("%ld %d %s\n", get_time(MILLISEC) - table->sim_start,
					table->philosophers[i].id, "died");
				pthread_mutex_unlock(&table->print_mtx);
			}
		}
	}
	return (NULL);
}
