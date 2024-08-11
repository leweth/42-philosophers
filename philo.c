/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/11 12:25:19 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void check_leaks(void)
{
	system("leaks -q philo");
}

int main(int argc, char **argv)
{
	t_process_data	p_data;
	u_int32_t		i;

	atexit(check_leaks);
	p_data.err = process_input(&p_data, argc, argv);
	if (p_data.err != NONE)
		return (print_error(p_data.err), FAILURE);
	init_variable(&p_data);
	if (p_data.err != NONE)
		return (print_error(p_data.err), FAILURE); 
	i = 1;
	while (i <= p_data.SIM_NUM_OF_PHILOS)
	{
		// pthread_create(p_data.philos->ptid, NULL, NULL, &p_data);
		i++;
	}
	clean_philos(p_data.philos, p_data.SIM_NUM_OF_PHILOS);
	clean_end_mark(p_data.end_mark);
}
