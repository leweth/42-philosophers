/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:12:58 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/15 19:37:46 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*new_philo(u_int32_t id, t_sim_info *sim, int16_t *error)
{
	t_philo	*philo;

	philo = (t_philo *) malloc(sizeof(t_philo));
	if (!philo)
		return (*error = FAILED_MALLOC_ERR, NULL);
	memset(philo, 0, sizeof(t_philo));
	(philo)->id = id + 1;
	(philo)->fork_lock = 
		(pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!philo->fork_lock)
		return (clean_philos(philo), *error = FAILED_MALLOC_ERR, NULL);
	pthread_mutex_init(philo->fork_lock, NULL); // what do they mean by initilize it? // you should dstroy this at the end
	philo->eating_counter = 0;
	philo->current_simulation = sim;
	philo->err = error;
  	return (philo);
}

int16_t	init_variable(t_philo **philo, t_sim_info *sim, int16_t *error)
{
	t_philo		*tmp;
	u_int32_t	i;

	sim->stop_simulation = false;
	sim->stop_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t *));
	pthread_mutex_init(sim->stop_lock, NULL);
	*philo = new_philo(0, sim, error);
	if (*error != NONE)
		return (*error);
	tmp = *philo;
	i = 1;
	while (i < sim->num_of_philos)
	{
		tmp->next = new_philo(i, sim, error);
		tmp = tmp->next;
		i++;
	}
	tmp->next = *philo;
	return (NONE);
}
