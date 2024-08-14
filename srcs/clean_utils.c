/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:15:15 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/14 17:51:33 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	clean_philos(t_philo *top) // frees fork locks and the array of philos
{
	t_philo		*pass;
	t_philo		*tmp;

	pass = top;
	while (pass)
	{
		tmp = pass->next;
		pthread_mutex_destroy(pass->fork_lock);
		free(pass->fork_lock);
		free(pass);
		pass = tmp;
	}
}
