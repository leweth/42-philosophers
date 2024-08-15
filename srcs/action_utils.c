/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:32:14 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/15 18:40:51 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	philo_take_fork(t_philo *philo, u_int32_t index)
{
	size_t	current_time;
	size_t	elapsed_time;
	int16_t	err;

	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->SIM_START_TIME;
	printf("%zu %u has taken a fork\n", elapsed_time, index);
	return (NONE);
}

int16_t	philo_eat(t_philo *philo, u_int32_t index)
{
	size_t	current_time;
	size_t	elapsed_time;
	int16_t		err;

	// check wether it is the time to eat if exceeded he has to die
	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->SIM_START_TIME;
	if (current_time - philo->last_time_ate > philo->SIM_TIME_TO_DIE)
	{
		printf("Current time: %zu\nLast time ate: %zu\nTime to die: %u\n", current_time, philo->last_time_ate, philo->SIM_TIME_TO_DIE);
		pthread_mutex_lock(philo->SIM_STOP_LOCK);
		philo->SIM_STOP = true;
		pthread_mutex_unlock(philo->SIM_STOP_LOCK);
		printf("%zu %u died\n", elapsed_time, index);
		return (DIED);
	}
	else
	{
		philo->last_time_ate = elapsed_time;
		printf("%zu %u is eating\n", elapsed_time, index);
	}
	return (NONE);
}

int16_t	philo_sleep(t_philo *philo, u_int32_t index)
{
	size_t	current_time;
	size_t	elapsed_time;
	int16_t		err;

	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->SIM_START_TIME;
	usleep(philo->SIM_TIME_TO_SLEEP * 1000);
	printf("%zu %u is sleeping\n", elapsed_time, index);
	return (NONE);
}

int16_t	philo_think(t_philo *philo, u_int32_t index)
{
	size_t	current_time;
	size_t	elapsed_time;
	int16_t		err;

	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->SIM_START_TIME;
	printf("%zu %u is thinking\n", elapsed_time, index);
	return (NONE);
}
