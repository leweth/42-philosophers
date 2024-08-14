/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/14 20:41:36 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/* void check_leaks(void)
{
	system("leaks -q philo");
} */

void	*simulate_sequence(void *data)
{
	t_philo			*philo;
	int16_t			err;

	philo = (t_philo *) data;
	usleep((philo->id - 1) * 10);
	while (true)
	{
		if (philo->SIM_STOP == true)
			break ;
		err = philo_sleep(philo, philo->id);
		pthread_mutex_lock(philo->fork_lock);
		pthread_mutex_lock((philo->next)->fork_lock);
		philo_take_fork(philo, philo->id);
		err = philo_eat(philo, philo->id);
		if (philo->died == true)
			break ;
		err = philo_think(philo, philo->id);
		philo->eating_counter++;
		pthread_mutex_unlock((philo->next)->fork_lock);
		pthread_mutex_unlock(philo->fork_lock);
		// error handling for later time
		if (philo->SIM_NUM_OF_TIMES_TO_EAT != UNSPECIFIED
			&& philo->eating_counter == philo->SIM_NUM_OF_TIMES_TO_EAT)
			break ;
	}
	return (NULL);
}

int64_t	extract_time(u_int32_t *start_time)
{
	struct timeval	tmp;
	int				err;

	err = gettimeofday(&tmp, NULL);
	if (err < 0)
		return (ERROR_IN_GETTING_TIME);
	*start_time = tmp.tv_sec * 100;
	return (NONE);
}

int main(int argc, char **argv)
{
	t_philo		*philo;
	t_philo		*pass;
	int16_t		error;
	t_sim_info	sim;
	u_int32_t	i;

	// atexit(check_leaks);
	process_input(&sim, argc, argv, &error);
	if (error != NONE)
		return (print_error(error), FAILURE);
	init_variable(&philo, &sim, &error);
	if (error != NONE)
		return (print_error(error), FAILURE);
	extract_time(&sim.start_time);
	i = 0;
	pass = philo;
	while (i < sim.num_of_philos)
	{
		pthread_create(&(pass->ptid), NULL, simulate_sequence, pass); // has assosciated resources
		pass = pass->next;
		i++;
	}
	pass = philo;
	i = 0;
	while (i < sim.num_of_philos)
	{
		pthread_join(pass->ptid, NULL);
		pass = pass->next;
		i++;
	}
	clean_philos(philo);
}
