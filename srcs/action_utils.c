/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:32:14 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/14 19:38:16 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	philo_take_fork(t_philo *philo, u_int32_t index)
{
	u_int32_t	current_time;
	u_int32_t	elapsed_time;
	int16_t		err;

	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->SIM_START_TIME;
	printf("%u %u has taken a fork\n", elapsed_time, index);
	return (NONE);
}

int16_t	philo_eat(t_philo *philo, u_int32_t index)
{
	u_int32_t	current_time;
	u_int32_t	elapsed_time;
	int16_t		err;

	// check wether it is the time to eat if exceeded he has to die
	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->SIM_START_TIME;
	if (current_time - philo->last_time_ate > philo->SIM_TIME_TO_DIE)
		return (philo->died = true, printf("%u %u died\n", elapsed_time, index), DIED);
	else
		{
			philo->last_time_ate = elapsed_time;
			printf("%u %u is eating\n", elapsed_time, index);
		}
	return (NONE);
}

int16_t	philo_sleep(t_philo *philo, u_int32_t index)
{
	u_int32_t	current_time;
	u_int32_t	elapsed_time;
	int16_t		err;

	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->SIM_START_TIME;
	usleep(philo->SIM_TIME_TO_SLEEP * 1000);
	printf("%u %u is sleeping\n", elapsed_time, index);
	return (NONE);
}

int16_t	philo_think(t_philo *philo, u_int32_t index)
{
	u_int32_t	current_time;
	u_int32_t	elapsed_time;
	int16_t		err;

	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->SIM_START_TIME;
	printf("%u %u is thinking\n", elapsed_time, index);
	return (NONE);
}
