/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:15:15 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/15 18:44:47 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_philos(t_philo *top) // frees fork locks and the array of philos
{
	t_philo		*pass;
	t_philo		*tmp;
	t_sim_info	*sim;
	uint32_t	i;

	i = 0;
	pass = top;
	pthread_mutex_destroy(top->SIM_STOP_LOCK);
	free(top->SIM_STOP_LOCK);
	sim = top->current_simulation;
	while (i < sim->num_of_philos)
	{
		tmp = pass->next;
		pthread_mutex_destroy(pass->fork_lock);
		free(pass->fork_lock);
		free(pass);
		pass = 0;
		pass = tmp;
		i++;
	}
}
