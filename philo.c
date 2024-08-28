/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/28 11:00:15 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/* void check_leaks(void)
{
	system("leaks -q philo");
} */

void	*simulate_sequence(void *data)
{
	t_philo	*philo;
	int16_t	err;

	philo = (t_philo *) data;
	safe_extract(&philo->last_time_ate, philo->la_lock);
	while (true)
	{
		if (should_stop(philo->c_sim))
			break ;
		err = philo_think(philo);
		if (philo->id % 2 == 0)
			err = philo_sleep(philo);
		pthread_mutex_lock(philo->fork_lock); // **
		pthread_mutex_lock((philo->next)->fork_lock); // ==
		philo_take_fork(philo);
		err = philo_eat(philo);
		philo->eating_counter++;
		pthread_mutex_unlock((philo->next)->fork_lock); // ==
		pthread_mutex_unlock(philo->fork_lock); // ** 
		if (philo->id % 2 == 1)
			err = philo_sleep(philo);
		if ((philo->c_sim->num_of_times_to_eat != UNSPECIFIED
			&& philo->eating_counter == philo->c_sim->num_of_times_to_eat))
				set_stop(philo->c_sim);
	}
	return (NULL);
}

void	observer(t_philo *philo)
{
	t_philo	*pass;
size_t	current_time;
size_t	elapsed_time;

	pass = philo;
	usleep(200);
	while (true)
	{
		pthread_mutex_lock(pass->la_lock);
		extract_time(&current_time);
		if (current_time - pass->last_time_ate >= philo->c_sim->time_to_die)
		{
			set_stop(pass->c_sim);
			elapsed_time = current_time - philo->c_sim->start_time;
			safe_message(philo, "died", elapsed_time);
		}
		pthread_mutex_unlock(pass->la_lock);
		if (should_stop(philo->c_sim))
			break ;
		pass = pass->next;
	}
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
	i = 0;
	pass = philo;
	extract_time(&sim.start_time);
	while (i < sim.num_of_philos)
	{
		pthread_create(&(pass->ptid), NULL, simulate_sequence, pass);
		pass = pass->next;
		i++;
	}
	observer(philo);
	i = 0;
	while (i < sim.num_of_philos)
	{
		pthread_join(pass->ptid, NULL);
		pass = pass->next;
		i++;
	}
	clean_philos(philo);
}
