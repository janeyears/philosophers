/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:44:33 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/01 13:51:47 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

# define ERR_ARGS "./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> optional: <number_of_times_each_philosopher_must_eat>"
# define ERR_ALLOC "Allocation has failed"
# define ERR_PARSE "Parsing has failed"



typedef struct s_args	t_args;

typedef struct s_fork
{
	int				f_id;
	pthread_mutex_t	f_lock;
}	t_fork;

typedef struct s_philo
{
	int	ph_id;
	t_fork	first_fork;
	t_fork	second_fork;
	t_args	*arg_info;
}	t_philo;

typedef struct s_args
{
	int		philo_amount;
	int		meals_amount;
	size_t	t_to_die;
	size_t	t_to_sleep;
	size_t	t_to_eat;
	t_philo	*philos;
	bool	philo_dead;
	t_fork	*forks;
}	t_args;

#endif