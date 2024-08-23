/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/23 20:52:43 by mben-yah         ###   ########.fr       */
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
	// pthread_mutex_lock(philo->la_lock);
	// if (philo->id == 1)
		// printf("DKHAL 1\n");
	extract_time(&philo->last_time_ate);
	// pthread_mutex_unlock(philo->la_lock);
	while (true)
	{
// printf("YO%u\n", philo->id);
		if (should_stop(philo->c_sim))
			break ;
// printf("OPS%u\n", philo->id);
		if (philo->id % 2 == 0)
			err = philo_sleep(philo, philo->id);
		err = philo_think(philo, philo->id);
		pthread_mutex_lock(philo->fork_lock); // **
		pthread_mutex_lock((philo->next)->fork_lock); // ==
		// printf("HNA?%u\n", philo->id);
		philo_take_fork(philo, philo->id);
		err = philo_eat(philo, philo->id);
		philo->eating_counter++;
		pthread_mutex_unlock((philo->next)->fork_lock); // ==
		pthread_mutex_unlock(philo->fork_lock); // ** 
		if (philo->id % 2 == 1)
			err = philo_sleep(philo, philo->id);
		if (philo->c_sim->num_of_times_to_eat != UNSPECIFIED
			&& philo->eating_counter == philo->c_sim->num_of_times_to_eat)
				set_stop(philo->c_sim);
		// printf("%u --\n", philo->id);
	}
	(void) err;
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo		*philo;
	t_philo		*pass;
	int16_t		error;
	t_sim_info	sim;
	u_int32_t	i;

	// atexit(check_leaks);
	memset(&sim, 0, sizeof(t_sim_info));
	memset(&error, 0, sizeof(int16_t));
	process_input(&sim, argc, argv, &error);
	if (error != NONE)
		return (print_error(error), FAILURE);
	init_variable(&philo, &sim, &error);
	if (error != NONE)
		return (print_error(error), FAILURE);
	i = 0;
	pass = philo;
	extract_time(sim.start_time);
	while (i < sim.num_of_philos)
	{
		pthread_create(&(pass->ptid), NULL, simulate_sequence, pass);
		pass = pass->next;
		i++;
	}
	/* size_t	current_time;
size_t	elapsed_time;
	// printf("daz?\n");
	// millisleep(sim, 1000);
	while (true)
	{
		// pthread_mutex_lock(pass->la_lock);
		// printf("---%u---\n", philo->id);
		extract_time(&current_time);
		// printf("%zu %zu %u\n", current_time, pass->last_time_ate, sim.time_to_die);
		if (current_time - pass->last_time_ate > sim.time_to_die)
		{
			// printf("WSALTI?\n");
			set_stop(pass->c_sim);
			elapsed_time = current_time - sim.start_time;
			printf("%zu %u died\n", elapsed_time, pass->id);
		}
		// pthread_mutex_unlock(pass->la_lock);
		pass = pass->next;
		if (should_stop(&sim))
			break ;
	} */
	i = 0;
	pass = philo;
	while (i < sim.num_of_philos)
	{
		pthread_join(pass->ptid, NULL);
		pass = pass->next;
		i++;
	}
	clean_philos(philo);
}
