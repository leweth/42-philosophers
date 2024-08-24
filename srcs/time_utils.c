/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 19:54:28 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/23 22:33:54 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int64_t	extract_time(size_t *ctime)
{
	struct timeval	tmp;
	int				err;

	memset(&tmp, 0, sizeof(struct timeval));
	err = gettimeofday(&tmp, NULL);
	if (err < 0)
		return (ERROR_IN_GETTING_TIME);
	*ctime = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	return (NONE);
}

void	safe_extract(size_t *ctime, pthread_mutex_t *lock)
{

}

void	millisleep(t_sim_info sim, size_t msecs)
{
	size_t	current_time;
	size_t	goal_time;

	current_time = 0;
	extract_time(&current_time);
	goal_time = (current_time + msecs) * 1000;
	while (current_time * 1000 < goal_time)
	{
		if (should_stop(&sim))
			break ;
		usleep(200);
		extract_time(&current_time);
	}
}
