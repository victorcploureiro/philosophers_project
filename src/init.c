/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:17:32 by vcarrara          #+#    #+#             */
/*   Updated: 2024/10/30 14:47:22 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	forks_distribution(t_philosopher *philo, t_fork *fork, int pos)
{
	int	philo_nbr;

	philo_nbr = philo->table->philos_count;
	philo->left_fork = &fork[(pos + 1) % philo_nbr];
	philo->right_fork = &fork[pos];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &fork[pos];
		philo->right_fork = &fork[(pos + 1) % philo_nbr];
	}
}

static void	init_philo(t_table *table)
{
	int				i;
	t_philosopher	*philo;

	i = -1;
	while (++i < table->philos_count)
	{
		philo = table->philosophers + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->table = table;
		mutex_handler(&philo->philo_mtx, INIT);
		forks_distribution(philo, table->forks, i);
	}
}

void	init_table(t_table *table)
{
	int	i;

	i = -1;
	table->sim_end = false;
	table->all_threads_set = false;
	table->running_threads = 0;
	table->philosophers = malloc(sizeof(t_philosopher) * table->philos_count);
	if (table->philosophers == NULL)
		print_error("Init: Bad malloc");
	table->forks = malloc(sizeof(t_fork) * table->philos_count);
	if (table->forks == NULL)
		print_error("Init: Bad malloc");
	mutex_handler(&table->table_mtx, INIT);
	mutex_handler(&table->print_mtx, INIT);
	while (++i < table->philos_count)
	{
		mutex_handler(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	init_philo(table);
}
