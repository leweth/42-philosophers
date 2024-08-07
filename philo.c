/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/07 17:47:58 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	*thread_subroutine(void *arg)
{
	int	index;
	char	*str;

	index = *(int *)arg;
	if (index == 0)
		str = "OPS";
	else
		str = "Foo";
	printf("We got into the thread!\n");
	while (1)
		printf("%s\n", str);
	return NULL;
}

int	main(int argc, char **argv)
{
	pthread_t	thread_id[2];
	int i[2] = {0, 1};
	int	j;

	while (j < 2)
	{
		pthread_create(thread_id + j, NULL, thread_subroutine, i + j);
		j++;
	}
	// pthread_join(thread_id, NULL);
	while (1)
		printf("---\n");
}
