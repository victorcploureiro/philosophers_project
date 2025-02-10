/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcarrara <vcarrara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:58:49 by vcarrara          #+#    #+#             */
/*   Updated: 2024/10/24 12:17:46 by vcarrara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv))
		exit(EXIT_FAILURE);
	parsing(&table, argv);
	init_table(&table);
	dinner_start(&table);
	cleanup(&table);
}
