/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/11 18:28:21 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void check_leaks(void)
{
	system("leaks -q philo");
}

/* bool	check_leave(bool *arr, int64_t size) // I can make a thread just to check all this,
{
	int64_t	i;
	int64_t	count;

	i = 0;
	count = 0;
	while (i < size)
	{
		if (arr[i] == true)
			count++;
		i++;
	}
	if (count == size)
		return (true);
	else
		return (false);
} */

void	*simulate_sequence(void *data)
{
	t_process_data	*p_data;
	u_int32_t		index;

	p_data = (t_process_data *) data;
	index = p_data->current_philo_id - 1;
	while (true) // I need to keep track of the simulation's start and the last meal times
	{
		usleep(p_data->SIM_TIME_TO_SLEEP * 1000);
		pthread_mutex_lock(p_data->philos[index].fork_lock);
		// fork taking
		pthread_mutex_lock(p_data->philos[PHILO_INDEX_CHECK].fork_lock);
		// eat
		pthread_mutex_unlock(p_data->philos[PHILO_INDEX_CHECK].fork_lock);
		pthread_mutex_unlock(p_data->philos[index].fork_lock);
		// sleep
		// think
		p_data->philos[index].eating_counter++;
		if (p_data->SIM_NUM_OF_TIMES_TO_EAT != UNSPECIFIED
			&& p_data->philos[index].eating_counter == 
				p_data->SIM_NUM_OF_TIMES_TO_EAT)
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
	*start_time = tmp.tv_usec * 1000;
	return (NONE);
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
	extract_time(&p_data.SIM_START_TIME);
	i = 0;
	while (i < p_data.SIM_NUM_OF_PHILOS)
	{
		// pthread_create((p_data.philos)[i].ptid, NULL, NULL, &p_data);
		p_data.current_philo_id = ++i;
	}
	while (--i > -1)
		pthread_join((p_data.philos[i]).ptid, NULL);
	//  the whole following process could have being avoided if pthread join was used
	// since you'd be essentially freeing after all the threads end their work.
	/* while (1)
	{
		if (p_data.SIM_NUM_OF_TIMES_TO_EAT != UNSPECIFIED)
			p_data.SIM_STOP = check_leave(p_data.end_mark, 
				p_data.SIM_NUM_OF_PHILOS);
		if (p_data.SIM_STOP == true)
		{
			clean_philos(p_data.philos, p_data.SIM_NUM_OF_PHILOS);
			clean_end_mark(p_data.end_mark);
		}
	} */
	clean_philos(p_data.philos, p_data.SIM_NUM_OF_PHILOS);
	clean_end_mark(p_data.end_mark);
}
