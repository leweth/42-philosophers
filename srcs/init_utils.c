/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:12:58 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/14 15:22:15 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int16_t	init_variable(t_process_data *p_data)
{
	u_int32_t	i;

	p_data->current_simulation.stop_simulation = false;
	p_data->philos = 
		(t_philo *) malloc(sizeof(t_philo) * (p_data->SIM_NUM_OF_PHILOS + 1));
	if (!p_data->philos)
		return (p_data->err = FAILED_MALLOC_ERR, p_data->err);
	i = 0;
	while (i < p_data->SIM_NUM_OF_PHILOS)
	{
		p_data->philos[i].fork_lock = 
			(pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		if (!(p_data->philos[i].fork_lock))
			return (clean_philos(p_data->philos, i), 
				p_data->err = FAILED_MALLOC_ERR, p_data->err);
		pthread_mutex_init(p_data->philos[i].fork_lock, NULL); // what do they mean by initilize it? // you should dstroy this at the end
		p_data->philos[i].eating_counter = 0;
		i++;
	}
	p_data->current_philo_id = 1;
	return (NONE);
}
