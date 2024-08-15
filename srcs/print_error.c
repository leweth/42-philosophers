/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:56:13 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/15 13:05:35 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_error(int16_t err)
{
	if (err == INVALID_NUMBER_OF_ARGS)
		printf("Invalid number of arguments\n");
	else if (err == INVALID_NUMBER_FORMAT)
		printf("Invaid number format\n");
	else if (err == NUMBER_LIMIT_EXCEEDED)
		printf("The number limit was exceeded\n");
	else if (err == IMPOSSIBLE_TO_EAT_IN_TIME_FRAME)
		printf("Impossible for the philosophers to eat within \
the given timeframe.\n");
}
