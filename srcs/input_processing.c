/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:27:04 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/15 13:13:23 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	process_input(t_sim_info *sim, int argc, char **argv, int16_t *error)
{
	if (argc < 5 || argc > 6)
		return (INVALID_NUMBER_OF_ARGS);
	*error = NONE;
	sim->num_of_philos= ft_atou32(argv[1], error);
	sim->time_to_die = ft_atou32(argv[2], error);
	sim->time_to_eat = ft_atou32(argv[3], error);
	sim->time_to_sleep = ft_atou32(argv[4], error);
	if (*error != NONE)
		return (*error);
	if (argc == 6)
		sim->num_of_times_to_eat = ft_atou32(argv[5], error);
	else
		sim->num_of_times_to_eat = UNSPECIFIED;
	if (sim->time_to_eat > sim->time_to_die)
		*error = IMPOSSIBLE_TO_EAT_IN_TIME_FRAME;
	if (sim->num_of_times_to_eat == 0)
		*error = SUCCESS;
	if (*error != NONE)
		return (*error);
	return (NONE);
}
