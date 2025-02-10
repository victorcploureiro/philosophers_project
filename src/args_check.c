/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 18:42:31 by vcarrara          #+#    #+#             */
/*   Updated: 2024/12/11 11:46:41 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	validation(char *argv)
{
	int	i;

	i = 0;
	while (is_space(argv[i]))
		i++;
	if (argv[i] == '+')
		i++;
	else if (argv[i] == '-')
		return (print_error("Why so negative? Please only use positive int\n"));
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]))
			return (print_error("Invalid input, use only numbers"));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_args(int argc, char **argv)
{
	long long int	arg;
	int				i;

	if (argc < 5)
		return (print_error("Usage: number_of_philosophers time_to_die "
				"time_to_eat time_to_sleep "
				"[number_of_times_each_philosopher_must_eat]"));
	if (argc > 6)
		return (print_error("Too many arguments"));
	i = 1;
	while (argv[i])
	{
		arg = ft_atol(argv[i]);
		if (arg < 0)
			return (print_error("Why so negative? Use only positive args"));
		if (arg > INT_MAX)
			return (print_error("Way too big... INT_MAX limit"));
		validation(argv[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	parsing(t_table *table, char **argv)
{
	table->philos_count = ft_atol(argv[1]);
	if (table->philos_count > PHILO_MAX)
		table->philos_count = PHILO_MAX;
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (argv[5])
		table->meals_limit = ft_atol(argv[5]);
	else
		table->meals_limit = -1;
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		print_error("Do not test with time_to_die or time_to_eat or "
			"time_to_sleep set to values lower than 60 ms.");
}
