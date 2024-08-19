/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:32:14 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/19 22:41:17 by mben-yah         ###   ########.fr       */
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
	elapsed_time = current_time - philo->c_sim->start_time;
	if (!should_stop(philo->c_sim))
		printf("%zu %u has taken a fork\n", elapsed_time, index);
	return (NONE);
}

int16_t	philo_eat(t_philo *philo, u_int32_t index)
{
	size_t	current_time;
	size_t	elapsed_time;
	int16_t		err;

	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->c_sim->start_time;
	if (current_time - philo->last_time_ate > philo->c_sim->time_to_die)
	{
		pthread_mutex_lock(philo->c_sim->stop_lock);
		philo->c_sim->stop = true;
		pthread_mutex_unlock(philo->c_sim->stop_lock);
		printf("%zu %u died\n", elapsed_time, index);
		return (DIED);
	}
	else if (!should_stop(philo->c_sim))
	{
		extract_time(&philo->last_time_ate);
		millisleep(*(philo->c_sim), philo->c_sim->time_to_eat);
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
	elapsed_time = current_time - philo->c_sim->start_time;
	if (should_stop(philo->c_sim))
		return (NONE);
	millisleep(*(philo->c_sim), philo->c_sim->time_to_sleep);
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
	elapsed_time = current_time - philo->c_sim->start_time;
	if (!should_stop(philo->c_sim))
		printf("%zu %u is thinking\n", elapsed_time, index);
	return (NONE);
}
