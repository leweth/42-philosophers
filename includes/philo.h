/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:13:59 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/08 18:56:25 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdint.h>

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

/* Syntax beauty macros */

# define SIM_NUM_OF_PHILOS current_simulation.num_of_philos
# define SIM_TIME_TO_DIE current_simulation.time_to_die
# define SIM_TIME_TO_EAT current_simulation.time_to_eat
# define SIM_TIME_TO_SLEEP current_simulation.time_to_sleep
# define SIM_NUM_OF_TIMES_TO_EAT current_simulation.num_of_times_to_eat

/* Information about the current simulation */

typedef struct s_sim_info
{
	u_int32_t	num_of_philos;
	u_int32_t	time_to_die;
	u_int32_t	time_to_eat;
	u_int32_t	time_to_sleep;
	int64_t		num_of_times_to_eat; // should be initialized to UNSPECIFIED
	bool		stop_simulation;
}			t_sim_info;

/* Infomration about the philosopher */

typedef struct s_philo
{
	pthread_t		ptid;
	u_int32_t		id; // starts at 1
	bool			has_fork;
	pthread_mutex_t	*fork_lock;
}			t_philo;

/* Information about the current process */

typedef struct s_process_data
{
	t_philo		*philos;
	t_sim_info	current_simulation;
	int16_t		err;
}			t_process_data;

/* Input processing functions */

u_int32_t	ft_atou32(char *str, int16_t *err);
int16_t		process_input(t_process_data *p_data, int argc, char **argv);

/* Error printing function */
void		print_error(int16_t err);

#endif