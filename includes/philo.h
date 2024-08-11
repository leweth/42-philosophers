/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:13:59 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/11 19:05:33 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>

/* General utilities macros */

# define SUCCESS 0
# define FAILURE -1
# define NONE -98
# define UNSPECIFIED -99

/* Error Macros */

# define INVALID_NUMBER_OF_ARGS -11
# define INVALID_NUMBER_FORMAT -12
# define NUMBER_LIMIT_EXCEEDED -13
# define FAILED_MALLOC_ERR -14
# define ERROR_IN_GETTING_TIME -15

/* Syntax beauty macros */

# define SIM_NUM_OF_PHILOS current_simulation.num_of_philos
# define SIM_TIME_TO_DIE current_simulation.time_to_die
# define SIM_TIME_TO_EAT current_simulation.time_to_eat
# define SIM_TIME_TO_SLEEP current_simulation.time_to_sleep
# define SIM_NUM_OF_TIMES_TO_EAT current_simulation.num_of_times_to_eat
# define SIM_STOP current_simulation.stop_simulation
# define SIM_START_TIME current_simulation.start_time
# define PHILO_INDEX_CHECK (index + 1) * !(index == p_data->SIM_NUM_OF_PHILOS)

/* Information about the current simulation */

typedef struct s_sim_info
{
	u_int32_t	num_of_philos;
	u_int32_t	time_to_die;
	u_int32_t	time_to_eat;
	u_int32_t	time_to_sleep;
	int64_t		num_of_times_to_eat; // should be initialized to UNSPECIFIED
	bool		stop_simulation;
	u_int32_t	start_time;
}			t_sim_info;

/* Infomration about the philosopher */

typedef struct s_philo
{
	pthread_t		ptid;
	pthread_mutex_t	*fork_lock;
	int64_t			eating_counter;
	u_int32_t		last_time_ate;
}			t_philo;

/* Information about the current process */

typedef struct s_process_data
{
	t_philo		*philos;
	t_sim_info	current_simulation;
	u_int32_t	current_philo_id;
	bool		*end_mark;
	int16_t		err;
}			t_process_data;

/* Input processing functions */

u_int32_t	ft_atou32(char *str, int16_t *err);
int16_t		process_input(t_process_data *p_data, int argc, char **argv);

/* Initilialization utilities */

int16_t		init_variable(t_process_data *p_data);

/* Actions utilities */


/* Cleaning utilities */

void		clean_philos(t_philo *philos, u_int32_t current_index);
void		clean_end_mark(bool *end_mark);

/* Error printing function */
void		print_error(int16_t err);

#endif