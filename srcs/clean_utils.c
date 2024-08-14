/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:15:15 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/14 14:40:15 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_philos(t_philo *philos, u_int32_t current_index) // frees fork locks and the array of philos
{
	u_int32_t	i;

	i = 0;
	while (i < current_index)
	{
		pthread_mutex_destroy(philos[i].fork_lock);
		free(philos[i].fork_lock);
		i++;
	}
	free(philos);
}
