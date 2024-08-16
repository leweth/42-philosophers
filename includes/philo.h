/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-yah <mben-yah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 04:13:59 by mben-yah          #+#    #+#             */
/*   Updated: 2024/08/15 19:59:16 by mben-yah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

/* General utilities macros */

# define SUCCESS 0
# define FAILURE -1
# define NONE -98
# define UNSPECIFIED -99
# define DIED -100

/* Error Macros */

# define IMPOSSIBLE_TO_EAT_IN_TIME_FRAME -10
# define INVALID_NUMBER_OF_ARGS -11
# define INVALID_NUMBER_FORMAT -12
# define NUMBER_LIMIT_EXCEEDED -13
# define FAILED_MALLOC_ERR -14
# define ERROR_IN_GETTING_TIME -15

/* Syntax beauty macros */

# define SIM_NUM_OF_PHILOS current_simulation->num_of_philos
# define SIM_TIME_TO_DIE current_simulation->time_to_die
# define SIM_TIME_TO_EAT current_simulation->time_to_eat
# define SIM_TIME_TO_SLEEP current_simulation->time_to_sleep
# define SIM_NUM_OF_TIMES_TO_EAT current_simulation->num_of_times_to_eat
# define SIM_STOP current_simulation->stop_simulation
# define SIM_STOP_LOCK current_simulation->stop_lock
# define SIM_START_TIME current_simulation->start_time

/* Information about the current simulation */

typedef struct s_sim_info
{
	u_int32_t		num_of_philos;
	u_int32_t		time_to_die;
	u_int32_t		time_to_eat;
	u_int32_t		time_to_sleep;
	int64_t			num_of_times_to_eat; // should be initialized to UNSPECIFIED
	bool			stop_simulation;
	pthread_mutex_t	*stop_lock;
	size_t			start_time;
}			t_sim_info;

/* Infomration about the philosopher */

typedef struct s_philo
{
	u_int32_t		id;
	pthread_t		ptid;
	pthread_mutex_t	*fork_lock; // a malloc and has some associated resources on some implementations
	int64_t			eating_counter;
	size_t			last_time_ate;
	t_sim_info		*current_simulation;
	int16_t			*err;
	struct s_philo	*next;
}			t_philo;

/* Actions function prototype defined */

typedef int16_t (*philo_action)(t_philo *, u_int32_t);

/* Input processing functions */

u_int32_t	ft_atou32(char *str, int16_t *err);
int16_t		process_input(t_sim_info *sim, int argc, char **argv, int16_t *error);

/* Initilialization utilities */

int16_t		init_variable(t_philo **philo, t_sim_info *sim, int16_t *error);

/* Actions utilities */

int16_t		philo_take_fork(t_philo *philo, u_int32_t index);
int16_t		philo_eat(t_philo *philo, u_int32_t index);
int16_t		philo_sleep(t_philo *philo, u_int32_t index);
int16_t		philo_think(t_philo *philo, u_int32_t index);

/* Cleaning utilities */

void		clean_philos(t_philo *top);

/* Time utils */

void		millisleep(size_t msecs);
int64_t		extract_time(size_t *start_time);

/* Error printing function */
void		print_error(int16_t err);

#endif