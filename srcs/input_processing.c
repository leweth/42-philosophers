/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:27:04 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/14 14:31:27 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	process_input(t_process_data *p_data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (INVALID_NUMBER_OF_ARGS);
	p_data->err = NONE;
	p_data->SIM_NUM_OF_PHILOS = ft_atou32(argv[1], &p_data->err);
	p_data->SIM_TIME_TO_DIE = ft_atou32(argv[2], &p_data->err);
	p_data->SIM_TIME_TO_EAT = ft_atou32(argv[3], &p_data->err);
	p_data->SIM_TIME_TO_SLEEP = ft_atou32(argv[4], &p_data->err);
	if (p_data->err != NONE)
		return (p_data->err);
	if (argc == 6)
		p_data->SIM_NUM_OF_TIMES_TO_EAT = ft_atou32(argv[4], &p_data->err);
	else
		p_data->SIM_NUM_OF_TIMES_TO_EAT = UNSPECIFIED;
	if (p_data->err != NONE)
		return (p_data->err);
	return (NONE);
}
