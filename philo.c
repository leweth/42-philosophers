/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/28 17:50:32 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void check_leaks(void)
{
	system("leaks -q philo");
}

void	simulate_lone_philo(t_philo *philo)
{
	size_t	current_time;

	current_time = 0;
	millisleep(*(philo->c_sim), philo->c_sim->time_to_die);
	extract_time(&current_time);
	safe_message(philo, "died", current_time - philo->c_sim->start_time);
	pthread_mutex_unlock(philo->fork_lock);
}

void	*simulate_sequence(void *data)
{
	t_philo	*philo;
	int16_t	err;

	philo = (t_philo *) data;
	safe_extract(&philo->last_time_ate, philo->la_lock);
		if (philo->id % 2 == 0)
			err = philo_sleep(philo);
	while (true)
	{
		if (should_stop(philo->c_sim))
			break ;
		err = philo_think(philo);
		pthread_mutex_lock(philo->fork_lock); // **
		if (philo->c_sim->num_of_philos == 1)
			return (simulate_lone_philo(philo), NULL);
		pthread_mutex_lock((philo->next)->fork_lock); // ==
		philo_take_fork(philo);
		err = philo_eat(philo);
		philo->eating_counter++;
		pthread_mutex_unlock((philo->next)->fork_lock); // ==
		pthread_mutex_unlock(philo->fork_lock); // ** 
		// if (philo->id % 2 == 1)
			err = philo_sleep(philo);
		if ((philo->c_sim->num_of_times_to_eat != UNSPECIFIED
			&& philo->eating_counter == philo->c_sim->num_of_times_to_eat))
				{philo->finished = true; break ;}
	}
	return (NULL);
}

bool	done_eating(t_philo *philo)
{
	uint32_t	i;
	uint32_t	sum;

	i = 0;
	sum = 0;
	while (i < philo->c_sim->num_of_philos)
	{
		sum += philo->finished;
		philo = philo->next;
		i++;
	}
	if (sum == philo->c_sim->num_of_philos)
		return (true);
	return (false);
}

void	observer(t_philo *philo)
{
	t_philo	*pass;
size_t	current_time;
size_t	elapsed_time;

	if (philo->c_sim->num_of_philos == 1)
		return ;
	pass = philo;
	usleep(50);
	while (true)
	{
		pthread_mutex_lock(pass->la_lock);
		extract_time(&current_time);
		if (current_time - pass->last_time_ate >= philo->c_sim->time_to_die
			&& philo->finished == false)
		{
			set_stop(pass->c_sim);
			elapsed_time = current_time - philo->c_sim->start_time;
			safe_message(philo, "died", elapsed_time);
		}
		pthread_mutex_unlock(pass->la_lock);
		if (done_eating(philo))
			break ;
		if (should_stop(philo->c_sim))
			break ;
		pass = pass->next;
	}
}

void	run_simulation(t_philo *philo)
{
	t_philo		*pass;
	u_int32_t	i;

	i = 0;
	pass = philo;
	extract_time(&philo->c_sim->start_time);
	while (i < philo->c_sim->num_of_philos)
	{
		pthread_create(&(pass->ptid), NULL, simulate_sequence, pass);
		pass = pass->next;
		i++;
	}
	observer(philo);
	i = 0;
	while (i < philo->c_sim->num_of_philos)
	{
		pthread_join(pass->ptid, NULL);
		pass = pass->next;
		i++;
	}
}

int main(int argc, char **argv)
{
	t_philo		*philo;
	t_error		err;
	t_sim_info	sim;

	atexit(check_leaks);
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
	clean_philos(philo);
}
