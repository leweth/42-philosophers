/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:15:15 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/28 18:12:08 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_lock(pthread_mutex_t *lock)
{
	pthread_mutex_destroy(lock);
	free(lock);
}

void	clean_sim(t_sim_info *sim)
{
	clean_lock(sim->printf_lock);
	clean_lock(sim->stop_lock);
}

void	clean_philos(t_philo *top)
{
	t_philo		*pass;
	t_philo		*tmp;
	t_sim_info	*sim;
	uint32_t	i;

	i = 0;
	if (!top)
		return ;
	sim = top->c_sim;
	pass = top;
	while (i < sim->num_of_philos)
	{
		tmp = pass->next;
		pthread_mutex_destroy(pass->fork_lock);
		pthread_mutex_destroy(pass->la_lock);
		free(pass->la_lock);
		free(pass->fork_lock);
		free(pass);
		pass = 0;
		pass = tmp;
		i++;
	}
}

void	clean_all(t_philo *philo, t_sim_info *sim, t_error *error)
{
	clean_sim(sim);
	clean_lock(error->err_lock);
	clean_philos(philo);
}
