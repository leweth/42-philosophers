/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:32:14 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/11 19:22:42 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	eat(t_process_data *p_data, u_int32_t index)
{
	u_int32_t	current_time;
	u_int32_t	elapsed_time;

	// check wether it is the time to eat if exceeded he has to die
	extract_time(&current_time);
	elapsed_time = current_time + p_data->SIM_START_TIME;
	if (current_time - (p_data->philos)[index].last_time_ate > p_data->SIM_TIME_TO_DIE)
		return (DIED);
	else
		printf("%u %u has eaten\n", elapsed_time, index);
}

