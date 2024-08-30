/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:12:58 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/30 19:36:12 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_sim(t_sim_info *sim, int16_t *error)
{
	int	res;

	res = 0;
	sim->stop = false;
	// printf("%p\n", &sim->stop);
	sim->stop_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!sim->stop_lock)
	{
		*error = FAILED_MALLOC_ERR;
		return ;
	}
	res = pthread_mutex_init(sim->stop_lock, NULL);
	sim->printf_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!sim->printf_lock)
	{
		*error = FAILED_MALLOC_ERR;
		return ;
	}
	res = pthread_mutex_init(sim->printf_lock, NULL);
	if (res)
	{	
		*error = FAILED_MUTEX_INIT;
		return ;
	}
}

void	init_error(t_error *error)
{
	int	res;

	error->err_code = NONE;
	error->err_lock = malloc(sizeof(pthread_mutex_t));
	if (!error->err_lock)
	{
		error->err_code = FAILED_MALLOC_ERR;
		return ;
	}
	res = pthread_mutex_init(error->err_lock, NULL);
	if (res)
	{	
		error->err_code = FAILED_MUTEX_INIT;
		return ;
	}
}

t_philo	*new_philo(u_int32_t id, t_sim_info *sim, t_error *error)
{
	t_philo	*philo;

	philo = (t_philo *) malloc(sizeof(t_philo));
	if (!philo)
		return (error->err_code = FAILED_MALLOC_ERR, NULL);
	(philo)->id = id;
	(philo)->fork_lock = 
		(pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!philo->fork_lock)
		return (clean_philos(philo), error->err_code = FAILED_MALLOC_ERR, NULL);
	pthread_mutex_init(philo->fork_lock, NULL); // what do they mean by initilize it? // you should dstroy this at the end
	philo->la_lock = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!philo->la_lock)
		return (clean_philos(philo), error->err_code = FAILED_MALLOC_ERR, NULL);
	(philo)->finish_lock = 
		(pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!philo->finish_lock)
		return (clean_philos(philo), error->err_code = FAILED_MALLOC_ERR, NULL);
	pthread_mutex_init(philo->la_lock, NULL);
	philo->eating_counter = 0;
	philo->c_sim = sim;
	philo->err = error;
	philo->finished = false;
  	return (philo);
}

void	init_variable(t_philo **philo, t_sim_info *sim, t_error *error)
{
	t_philo		*tmp;
	u_int32_t	i;

	*philo = new_philo(1, sim, error);
	if (error->err_code != NONE)
		return ;
	tmp = *philo;
	i = 1;
	while (i < sim->num_of_philos)
	{
		tmp->next = new_philo(i + 1, sim, error);
		tmp = tmp->next;
		i++;
	}
	tmp->next = *philo;
}
