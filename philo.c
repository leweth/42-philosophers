/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/07/25 07:12:21 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*thread_subroutine(void *arg)
{
	(void) arg;
	printf("We got into the thread!\n");
	while (1)
		printf("OPS\n");
	return NULL;
}

int	main(int argc, char **argv)
{
	pthread_t	thread_id;

	pthread_create(&thread_id, NULL, thread_subroutine, NULL);
	pthread_join(thread_id, NULL);
	while (1)
		printf("---\n");
}
