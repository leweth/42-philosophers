/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_manage_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:40:47 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/28 19:18:30 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_stop(t_sim_info *sim)
{
	pthread_mutex_lock(sim->stop_lock);
	sim->stop = true;
	pthread_mutex_unlock(sim->stop_lock);
}

bool	should_stop(t_sim_info *sim)
{
	bool	flag;

	flag = false;
	pthread_mutex_lock(sim->stop_lock);
	if (sim->stop == true)
		flag = true;
	pthread_mutex_unlock(sim->stop_lock);
	return (flag);
}

void	safe_message(t_philo *philo, const char *str, size_t timestamp)
{
	pthread_mutex_lock(philo->la_lock);
	printf("%zu %u %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(philo->la_lock);
}

void	safe_set(void *data, pthread_mutex_t *lock, int type, int value)
{
	pthread_mutex_lock(lock);
	if (type == INT_DTYPE)
		*((int *) data) = value;
	else
		*((bool *) data) = value;
	pthread_mutex_unlock(lock);
}

int16_t	safe_get_err_val(t_error *err)
{
	int16_t	value;

	pthread_mutex_lock(err->err_lock);
	value = err->err_code;	
	pthread_mutex_unlock(err->err_lock);
	return (value);
}
