/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:19:11 by vcarrara          #+#    #+#             */
/*   Updated: 2024/10/24 14:07:17 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mutex, bool *dst, bool value)
{
	mutex_handler(mutex, LOCK);
	*dst = value;
	mutex_handler(mutex, UNLOCK);
}

void	set_long(t_mtx *mutex, long *dst, long value)
{
	mutex_handler(mutex, LOCK);
	*dst = value;
	mutex_handler(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	result;

	mutex_handler(mutex, LOCK);
	result = *value;
	mutex_handler(mutex, UNLOCK);
	return (result);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	result;

	mutex_handler(mutex, LOCK);
	result = *value;
	mutex_handler(mutex, UNLOCK);
	return (result);
}

bool	end_sim(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->sim_end));
}
