/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:27:04 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/23 20:52:08 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	process_input(t_sim_info *sim, int argc, char **argv, t_error *error)
{
	memset(&sim, 0, sizeof(t_sim_info));
	memset(&error, 0, sizeof(t_error));
	error->err_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(error->err_lock, NULL);
	if (argc < 5 || argc > 6)
		return (error->err_code = INVALID_NUMBER_OF_ARGS, error->err_code);
	error->err_code = NONE;
	sim->num_of_philos= ft_atou32(argv[1], &error->err_code);
	sim->time_to_die = ft_atou32(argv[2], &error->err_code);
	sim->time_to_eat = ft_atou32(argv[3], &error->err_code);
	sim->time_to_sleep = ft_atou32(argv[4], &error->err_code);
	if (error->err_code != NONE)
		return (error->err_code);
	if (argc == 6)
		sim->num_of_times_to_eat = ft_atou32(argv[5], &error->err_code);
	else
		sim->num_of_times_to_eat = UNSPECIFIED;
	if (error->err_code != NONE)
		return (error->err_code);
	return (NONE);
}
