/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/19 19:00:25 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/* void check_leaks(void)
{
	system("leaks -q philo");
} */

bool	should_stop(t_sim_info *sim)
{
	bool	flag;

	flag = false;
	pthread_mutex_lock(sim->stop_lock);
	if (sim->stop_simulation == true)
		flag = true;
	pthread_mutex_unlock(sim->stop_lock);
	return (flag);
}

void	*simulate_sequence(void *data)
{
	t_philo			*philo;
	int16_t			err;
	bool			flag;

	flag = false;
	philo = (t_philo *) data;
	extract_time(&philo->last_time_ate);
	while (true)
	{
		pthread_mutex_lock(philo->c_sim->stop_lock); // --
		if (philo->c_sim->stop_simulation == true)
			flag = true ;
		pthread_mutex_unlock(philo->c_sim->stop_lock); // --
		if (flag)
			break ;
		if (philo->id % 2 == 0)
			err = philo_sleep(philo, philo->id);
		err = philo_think(philo, philo->id);
		pthread_mutex_lock(philo->fork_lock); // **
		pthread_mutex_lock((philo->next)->fork_lock); // ==
		philo_take_fork(philo, philo->id);
		err = philo_eat(philo, philo->id);
		philo->eating_counter++;
		pthread_mutex_unlock((philo->next)->fork_lock); // ==
		pthread_mutex_unlock(philo->fork_lock); // ** 
		if (philo->id % 2 == 1)
			err = philo_sleep(philo, philo->id);
		if (philo->c_sim->num_of_times_to_eat != UNSPECIFIED
			&& philo->eating_counter == philo->c_sim->num_of_times_to_eat)
		{
			pthread_mutex_lock(philo->c_sim->stop_lock);
			philo->c_sim->stop_simulation = true;
			pthread_mutex_unlock(philo->c_sim->stop_lock);
		}
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
	bool		flag;

	// atexit(check_leaks);
	memset(&sim, 0, sizeof(t_sim_info));
	process_input(&sim, argc, argv, &error);
	if (error != NONE)
		return (print_error(error), FAILURE);
	init_variable(&philo, &sim, &error);
	if (error != NONE)
		return (print_error(error), FAILURE);
	i = 0;
	pass = philo;
	extract_time(&philo->c_sim->start_time);
	while (i < sim.num_of_philos)
	{
		pthread_create(&(pass->ptid), NULL, simulate_sequence, pass);
		pass = pass->next;
		i++;
	}
	flag = false;
	while (true)
	{
		pthread_mutex_lock(philo->c_sim->stop_lock);
		if (philo->c_sim->stop_simulation == true)
			flag = true;
		pthread_mutex_unlock(philo->c_sim->stop_lock);
		if (flag == true)
			break ;
	}
	i = 0;
	while (i < sim.num_of_philos)
	{
		pthread_join(pass->ptid, NULL);
		pass = pass->next;
		i++;
	}
	clean_philos(philo);
}
