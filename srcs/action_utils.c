/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:32:14 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/14 15:23:03 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	philo_take_fork(t_process_data *p_data, u_int32_t index)
{
	u_int32_t	current_time;
	u_int32_t	elapsed_time;

	p_data->err = extract_time(&current_time);
	if (p_data->err != NONE)
		return (p_data->err);
	elapsed_time = current_time - p_data->SIM_START_TIME;
	printf("%u %u has taken a fork\n", elapsed_time, index);
	return (NONE);
}

int16_t	philo_eat(t_process_data *p_data, u_int32_t index)
{
	u_int32_t	current_time;
	u_int32_t	elapsed_time;

	// check wether it is the time to eat if exceeded he has to die
	p_data->err = extract_time(&current_time);
	if (p_data->err != NONE)
		return (p_data->err);
	elapsed_time = current_time - p_data->SIM_START_TIME;
	if (current_time - (p_data->philos)[index].last_time_ate > p_data->SIM_TIME_TO_DIE)
		return (printf("%u %u died\n", elapsed_time, index), DIED);
	else
		printf("%u %u is eating\n", elapsed_time, index);
	return (NONE);
}

int16_t	philo_sleep(t_process_data *p_data, u_int32_t index)
{
	u_int32_t	current_time;
	u_int32_t	elapsed_time;

	p_data->err = extract_time(&current_time);
	if (p_data->err != NONE)
		return (p_data->err);
	elapsed_time = current_time - p_data->SIM_START_TIME;
	usleep(p_data->SIM_TIME_TO_SLEEP * 1000);
	printf("%u %u is sleeping\n", elapsed_time, index);
	return (NONE);
}

int16_t	philo_think(t_process_data *p_data, u_int32_t index)
{
	u_int32_t	current_time;
	u_int32_t	elapsed_time;

	// check wether it is the time to eat if exceeded he has to die
	p_data->err = extract_time(&current_time);
	if (p_data->err != NONE)
		return (p_data->err);
	elapsed_time = current_time - p_data->SIM_START_TIME;
	printf("%u %u is thinking\n", elapsed_time, index);
	return (NONE);
}
