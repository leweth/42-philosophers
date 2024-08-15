/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/15 19:54:56 by mben-yah         ###   ########.fr       */
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
	bool			flag;

	flag = false;
	philo = (t_philo *) data;
	usleep((philo->id - 1) * 100);
	//  = philo->SIM_START_TIME;
	extract_time(&philo->last_time_ate);
	printf("ID: %u - Checking this out quite early: (%zu)\n", philo->id, philo->last_time_ate);
	while (true)
	{
		pthread_mutex_lock(philo->SIM_STOP_LOCK); // --
		if (philo->SIM_STOP == true)
			flag = true ;
		pthread_mutex_unlock(philo->SIM_STOP_LOCK); // --
		if (flag)
			break ;
		err = philo_think(philo, philo->id);
		pthread_mutex_lock(philo->fork_lock); // **
		pthread_mutex_lock((philo->next)->fork_lock); // ==
		philo_take_fork(philo, philo->id);
		printf("ID: %u - Checking this out another time: ((%zu))\n", philo->id, philo->last_time_ate);
		err = philo_eat(philo, philo->id);
		philo->eating_counter++;
		pthread_mutex_unlock((philo->next)->fork_lock); // ==
		pthread_mutex_unlock(philo->fork_lock); // ** 
		err = philo_sleep(philo, philo->id);
		if (philo->SIM_NUM_OF_TIMES_TO_EAT != UNSPECIFIED
			&& philo->eating_counter == philo->SIM_NUM_OF_TIMES_TO_EAT)
			break ;
	}
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
	extract_time(&sim.start_time);
	i = 0;
	pass = philo;
	while (i < sim.num_of_philos)
	{
		pthread_create(&(pass->ptid), NULL, simulate_sequence, pass);
		pass = pass->next;
		i++;
	}
	flag = false;
	while (true)
	{
		pthread_mutex_lock(philo->SIM_STOP_LOCK);
		if (philo->SIM_STOP == true)
			flag = true;
		pthread_mutex_unlock(philo->SIM_STOP_LOCK);
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
