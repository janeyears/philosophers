/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:06:15 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/05 17:29:51 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor_philos(t_args *args)
{
	size_t	i;
	size_t	time;

	while (1)
	{
		i = 0;
		while (i < args->philo_amount)
		{
			pthread_mutex_lock(&args->death_mutex);
			if (args->is_end == true)
			{
				pthread_mutex_unlock(&args->death_mutex);
				return ;
			}
			pthread_mutex_unlock(&args->death_mutex);
			time = get_time() - args->philos[i].t_last_meal;
			if (time >= args->t_to_die)
			{
				print_status(&args->philos[i], "died");
				confirm_death(args);
				return ;
			}
			i++;
		}
		ft_usleep(100);
	}
}

int	start_dinner(t_args *args)
{
	size_t	i;
	
	i = 0;
	while (i < args->philo_amount)
	{
		args->philos[i].t_last_meal = get_time();
		if (pthread_create(&args->philos[i].t_id, NULL, philo_routine,
				&args->philos[i]) != 0)
		{
			confirm_death(args);
			join_threads(args, i);
			return (error_msg(ERR_THREAD_PHILO), 1);
		}
		i++;
	}
	if (pthread_create(&args->monitor_thread, NULL, monitor_philos, args) != 0)
	{
		confirm_death(args);
		join_threads(args, args->philo_amount);
		return (error_msg(ERR_THREAD_MONITOR), 1);
	}
	join_threads(args, args->philo_amount);
	if (pthread_join(args->monitor_thread, NULL) != 0)
		return (error_msg(ERR_JOIN), 1);
	return (0);
}
