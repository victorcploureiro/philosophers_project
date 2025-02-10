/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:18:08 by vcarrara          #+#    #+#             */
/*   Updated: 2024/10/30 14:54:37 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

long	get_time(int time_code)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		print_error("Error getting time of day");
	if (MILLISEC == time_code)
		return (time.tv_sec * 1e3 + time.tv_usec / 1e3);
	else if (MICROSEC == time_code)
		return (time.tv_sec * 1e6 + time.tv_usec);
	else
		return (print_error("getimeofday: wrong input."));
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSEC);
	while (get_time(MICROSEC) - start < usec)
	{
		if (end_sim(table))
			break ;
		elapsed = get_time(MICROSEC) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
			while (get_time(MICROSEC) - start < usec)
				;
	}
}

void	write_status(t_status status, t_philosopher *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISEC) - philo->table->sim_start;
	if (philo->full)
		return ;
	mutex_handler(&philo->table->print_mtx, LOCK);
	if ((status == FIRST_FORK || status == SECOND_FORK)
		&& !end_sim(philo->table))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !end_sim(philo->table))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING && !end_sim(philo->table))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !end_sim(philo->table))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DEAD)
		printf("%-6ld %d died\n", elapsed, philo->id);
	mutex_handler(&philo->table->print_mtx, UNLOCK);
}

void	cleanup(t_table *table)
{
	t_philosopher	*philo;
	int				i;

	i = -1;
	while (++i < table->philos_count)
	{
		philo = table->philosophers + i;
		mutex_handler(&philo->philo_mtx, DESTROY);
	}
	mutex_handler(&table->print_mtx, DESTROY);
	mutex_handler(&table->table_mtx, DESTROY);
	free(table->forks);
	free(table->philosophers);
}
