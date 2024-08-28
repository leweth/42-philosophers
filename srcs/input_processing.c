/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:27:04 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/28 18:10:38 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	process_input(t_sim_info *sim, int argc, char **argv, t_error *error)
{
	init_error(error);
	init_sim(sim, &(error->err_code));
	if (argc < 5 || argc > 6)
	{
		error->err_code = INVALID_NUMBER_OF_ARGS;
		return ;
	}
	sim->num_of_philos= ft_atou32(argv[1], &(error->err_code));
	sim->time_to_die = ft_atou32(argv[2], &(error->err_code));
	sim->time_to_eat = ft_atou32(argv[3], &(error->err_code));
	sim->time_to_sleep = ft_atou32(argv[4], &(error->err_code));
	if (error->err_code != NONE)
		return ;
	if (argc == 6)
		sim->num_of_times_to_eat = ft_atou32(argv[5], &(error->err_code));
	else
		sim->num_of_times_to_eat = UNSPECIFIED;
	if (error->err_code != NONE)
		return ;
}
