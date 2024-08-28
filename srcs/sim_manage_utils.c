/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_manage_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:40:47 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/28 10:07:15 by mben-yah         ###   ########.fr       */
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
/* 
void	safe_access(void *data, pthread_mutex_t *lock)
{

} */
