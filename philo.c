/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:36:19 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/08 19:07:10 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/* void	*thread_subroutine(void *arg)
{
	int	index;
	char	*str;

	index = *(int *)arg;
	pthread_mutex_lock();
	pthread_mutex_unlock();
	if (index == 0)
		str = "OPS";
	else
		str = "Foo";
	printf("We got into the thread!\n");
	int start = 100;
	while (start--)
		printf("%s\n", str);
	printf("END?%d\n", index);
	return NULL;
}

int	main(int argc, char **argv)
{
	pthread_t	thread_id[2];
	// int i[2] = {0, 1};
	int	j = 0;
	int	i = 0;

	(void) argc;
	(void) argv;
	while (i < 2)
	{
		// pthread_create(thread_id + j, NULL, thread_subroutine, i + j);
		pthread_create(thread_id + i, NULL, thread_subroutine, i);
		i++;
	}
	for (int i=0; i < 44; i++)
		printf("The usual stuff\n");
	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);
} */

void	ft_clean(t_philo *philos, u_int32_t current_index)
{
	u_int32_t	i;

	i = 0;
	while (i < current_index)
		free(philos[i++].fork_lock);
	free(philos);
}

int16_t	init_variable(t_process_data *p_data)
{
	u_int32_t	i;

	p_data->current_simulation.stop_simulation = false;
	p_data->philos = 
		(t_philo *) malloc(sizeof(t_philo) * (p_data->SIM_NUM_OF_PHILOS + 1));
	if (!p_data->philos)
		return (p_data->err = FAILED_MALLOC_ERR, p_data->err);
	i = 0;
	while (i <= p_data->SIM_NUM_OF_PHILOS)
	{
		p_data->philos[i].id = i;
		p_data->philos[i].has_fork = true;
		p_data->philos[i].fork_lock = 
			(pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
		if (!(p_data->philos[i].fork_lock))
			return (ft_clean(p_data->philos, i), 
				p_data->err = FAILED_MALLOC_ERR, p_data->err);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_process_data	p_data;
	u_int32_t		i;

	p_data.err = process_input(&p_data, argc, argv);
	if (p_data.err != NONE)
		return (print_error(p_data.err), FAILURE);
	init_variable(&p_data);
	i = 1;
	while (i <= p_data.SIM_NUM_OF_PHILOS)
	{
		pthread_create(p_data.philos->ptid, NULL, NULL, &p_data);
	}
}
