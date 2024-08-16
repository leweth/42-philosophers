/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 19:54:28 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/15 19:58:35 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int64_t	extract_time(size_t *start_time)
{
	struct timeval	tmp;
	int				err;

	err = gettimeofday(&tmp, NULL);
	if (err < 0)
		return (ERROR_IN_GETTING_TIME);
	*start_time = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	return (NONE);
}

void	millisleep(size_t msecs)
{
	size_t	current_time;
	size_t	goal_time;

	extract_time(&current_time);
	goal_time = (current_time + msecs) * 1000;
	while (current_time < goal_time)
	{
		usleep(200);
		extract_time(&current_time);
	}
}
