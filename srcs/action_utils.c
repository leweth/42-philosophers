/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:32:14 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/23 20:00:23 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	philo_take_fork(t_philo *philo, u_int32_t index)
{
	size_t	current_time;
	size_t	elapsed_time;
	int16_t	err;

	current_time = 0;
	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->c_sim->start_time;
	if (!should_stop(philo->c_sim))
	{
		// pthread_mutex_lock(philo->c_sim->printf_lock);
		printf("%zu %u has taken a fork\n", elapsed_time, index);
		// pthread_mutex_unlock(philo->c_sim->printf_lock);
	}
	return (NONE);
}

int16_t	philo_eat(t_philo *philo, u_int32_t index)
{
	size_t	current_time;
	size_t	elapsed_time;
	int16_t		err;

	current_time = 0;
	// printf("YO%u\n", philo->id);
	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->c_sim->start_time;
	if (current_time - philo->last_time_ate >= philo->c_sim->time_to_die)
	{
		set_stop(philo->c_sim);
		// pthread_mutex_lock(philo->c_sim->printf_lock);
		printf("%zu %u died\n", elapsed_time, index);
		// pthread_mutex_unlock(philo->c_sim->printf_lock);
		return (DIED);
	}
	else 
	if (!should_stop(philo->c_sim))
	{
		// pthread_mutex_lock(philo->c_sim->printf_lock);
		printf("%zu %u is eating\n", elapsed_time, index);
		// pthread_mutex_unlock(philo->c_sim->printf_lock);
		// pthread_mutex_lock(philo->la_lock);
		extract_time(&philo->last_time_ate);
		// pthread_mutex_unlock(philo->la_lock);
		millisleep(*(philo->c_sim), philo->c_sim->time_to_eat);
	}
	return (NONE);
}

int16_t	philo_sleep(t_philo *philo, u_int32_t index)
{
	size_t	current_time;
	size_t	elapsed_time;
	int16_t		err;

	current_time = 0;
	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->c_sim->start_time;
	if (should_stop(philo->c_sim))
		return (NONE);
	// pthread_mutex_lock(philo->c_sim->printf_lock);
	printf("%zu %u is sleeping\n", elapsed_time, index);
	// pthread_mutex_unlock(philo->c_sim->printf_lock);

	millisleep(*(philo->c_sim), philo->c_sim->time_to_sleep);
	return (NONE);
}

int16_t	philo_think(t_philo *philo, u_int32_t index)
{
	size_t	current_time;
	size_t	elapsed_time;
	int16_t		err;

	current_time = 0;
	err = extract_time(&current_time);
	if (err != NONE)
		return (err);
	elapsed_time = current_time - philo->c_sim->start_time;
	if (!should_stop(philo->c_sim))
	{
		// pthread_mutex_lock(philo->c_sim->printf_lock);
		printf("%zu %u is thinking\n", elapsed_time, index);
		// pthread_mutex_unlock(philo->c_sim->printf_lock);
	}
	return (NONE);
}
