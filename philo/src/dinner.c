/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:06:15 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/14 15:27:34 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(t_philo *philo, int is_eating)
{
	int	sleep_chunk;
	int	remaining_time;

	if (philo->arg_info->t_to_die >= 60)
		sleep_chunk = philo->arg_info->t_to_die / 10;
	else
		sleep_chunk = philo->arg_info->t_to_die;
	if (is_eating)
		remaining_time = philo->arg_info->t_to_eat;
	else
		remaining_time = philo->arg_info->t_to_sleep;
	while (check_death_end(philo->arg_info) && remaining_time > 0)
	{
		ft_usleep(sleep_chunk, philo->arg_info);
		remaining_time -= sleep_chunk;
		if (remaining_time < sleep_chunk)
			sleep_chunk = remaining_time;
	}
}

static void	join_threads(t_args *args, size_t count)
{
	while (count > 0)
	{
		count--;
		if (pthread_join(args->philos[count].t_id, NULL) != 0)
			error_msg(ERR_JOIN);
	}
}

int	start_dinner(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_amount)
	{
		args->philos[i].t_last_meal = get_time();
		if (pthread_create(&args->philos[i].t_id, NULL, philo_routine,
				&args->philos[i]) != 0)
		{
			assign_death_end(args);
			join_threads(args, i);
			return (error_msg(ERR_THREAD_PHILO), 1);
		}
		i++;
	}
	if (pthread_create(&args->monitor_thread, NULL, monitoring, args) != 0)
	{
		assign_death_end(args);
		join_threads(args, args->philo_amount);
		return (error_msg(ERR_THREAD_MONITOR), 1);
	}
	join_threads(args, args->philo_amount);
	if (pthread_join(args->monitor_thread, NULL) != 0)
		return (error_msg(ERR_JOIN), 1);
	return (0);
}
