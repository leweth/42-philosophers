/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/28 22:08:37 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/* void check_leaks(void)
{
	system("leaks -q philo");
} */

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_error		err;
	t_sim_info	sim;

	// atexit(check_leaks);
	philo = NULL;
	process_input(&sim, argc, argv, &err);
	if (err.err_code != NONE || !sim.num_of_philos)
		return (print_error(err.err_code), clean_all(philo, &sim, &err),
			FAILURE);
	init_variable(&philo, &sim, &err);
	if (err.err_code != NONE)
		return (print_error(err.err_code), clean_all(philo, &sim, &err),
			FAILURE);
	run_simulation(philo);
	clean_all(philo, &sim, &err);
}
