/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:44:33 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/04 21:20:17 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define ERR_ARGS "./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> optional: <number_of_times_each_philosopher_must_eat>"
# define ERR_ALLOC "Allocation has failed"
# define ERR_ONE "There must be at least one philosopher and one meal if applicable"
# define ERR_NEG "Negative numbers are not allowed"
# define ERR_NOTINT "Input must be an integer"
# define ERR_TIME "Time values must be greater than 60ms"
# define ERR_OVERFLOW "Int overflow detected or too many philosophers"
# define ERR_INIT "Initialization has failed"

typedef struct s_args	t_args;

typedef struct s_fork
{
	int				f_id;
	pthread_mutex_t	f_lock;
}	t_fork; 

typedef struct s_philo
{	
	t_args		*arg_info;
	int			ph_id;	
	t_fork		*left_fork;
	t_fork		*right_fork;
	bool		is_full;
	size_t		t_last_meal;
	pthread_t	t_id;
}	t_philo;

typedef struct s_args
{
	long	philo_amount;
	long	meals_amount;
	size_t 	t_start;
	size_t	t_to_die;
	size_t	t_to_sleep;
	size_t	t_to_eat;
	t_philo	*philos;	
	t_fork	*forks;
	bool	is_end;
}	t_args;


void	*error_msg(char *message);

#endif