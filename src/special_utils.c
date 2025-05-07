/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:09:15 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/07 14:37:09 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time(void)
{
	struct timeval	tv;
	size_t			time;

	if (gettimeofday(&tv, NULL) == -1)
		return (error_msg(ERR_GETTIME), 0);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	assign_death_end(t_args *args)
{
		pthread_mutex_lock(&args->death_mutex);
		args->is_end = true;
		pthread_mutex_unlock(&args->death_mutex);
}

void	destroy_and_free(t_args *args)
{
	size_t	i;

	i = 0;
	while (i < args->philo_amount)
	{
		pthread_mutex_destroy(&args->forks[i].f_lock);
		i++;
	}
	pthread_mutex_destroy(&args->print_mutex);
	pthread_mutex_destroy(&args->death_mutex);
	free(args->forks);
	free(args->philos);
	free(args);
}

void	check_time_for_odd(t_philo *philo)
{
	if (philo->t_next_meal - get_current_time() > 0
		&& philo->ph_id % 2 == 1)
			ft_usleep(philo->t_next_meal - get_time());
}

void	single_lunch(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->f_lock);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->arg_info->t_to_die);
}