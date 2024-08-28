/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:32:14 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/28 10:54:50 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	philo_take_fork(t_philo *philo)
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
		safe_message(philo, "has taken a fork", elapsed_time);
	return (NONE);
}

int16_t	philo_eat(t_philo *philo)
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
		safe_message(philo, "is eating", elapsed_time);
		safe_extract(&philo->last_time_ate, philo->la_lock);
		millisleep(*(philo->c_sim), philo->c_sim->time_to_eat);
	}
	return (NONE);
}

int16_t	philo_sleep(t_philo *philo)
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
	safe_message(philo, "is sleeping", elapsed_time);
	millisleep(*(philo->c_sim), philo->c_sim->time_to_sleep);
	return (NONE);
}

int16_t	philo_think(t_philo *philo)
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
		safe_message(philo, "is thinking", elapsed_time);
	return (NONE);
}
