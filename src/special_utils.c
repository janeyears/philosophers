/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:09:15 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/05 17:33:03 by ekashirs         ###   ########.fr       */
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

void	print_status(t_philo *philo, char *status)
{
	size_t	time;

	time = get_time() - philo->t_last_meal;
	pthread_mutex_lock(&philo->arg_info->print_mutex);
	if (!philo->is_full)
		printf("%zu %d %s\n",time, philo->ph_id, status);
	pthread_mutex_unlock(&philo->arg_info->print_mutex);
}

void confirm_death(t_args *args)
{
		pthread_mutex_lock(&args->death_mutex);
		args->is_end = true;
		pthread_mutex_unlock(&args->death_mutex);
}

void join_threads(t_args *args, size_t count)
{
	while (count > 0)
	{
		count--;
		if (pthread_join(args->philos[count].t_id, NULL) != 0)
			error_msg(ERR_JOIN);
	}
}