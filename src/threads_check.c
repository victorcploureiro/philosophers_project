/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:51:32 by vcarrara          #+#    #+#             */
/*   Updated: 2024/10/24 12:23:57 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	add_long(t_mtx *mutex, long *value)
{
	mutex_handler(mutex, LOCK);
	(*value)++;
	mutex_handler(mutex, UNLOCK);
}

bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr)
{
	bool	result;

	result = false;
	mutex_handler(mutex, LOCK);
	if (*threads == philo_nbr)
		result = true;
	mutex_handler(mutex, UNLOCK);
	return (result);
}

void	unsync(t_philosopher *philo)
{
	if (philo->table->philos_count % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_threads_set))
		;
}
