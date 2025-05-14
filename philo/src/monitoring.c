/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:16:56 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/14 15:54:12 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death_end(t_args *args)
{
	pthread_mutex_lock(&args->death_mutex);
	if (args->is_end == true)
	{
		pthread_mutex_unlock(&args->death_mutex);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&args->death_mutex);
		return (1);
	}
}

static int	check_starvation(t_args *args, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&args->death_mutex);
	time = get_time() - philo->t_last_meal;
	if (time >= args->t_to_die && !philo->is_eating)
	{
		pthread_mutex_unlock(&args->death_mutex);
		print_status(philo, "died");
		assign_death_end(args);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&args->death_mutex);
		return (1);
	}
}

static int	check_meals_done(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_amount)
	{
		pthread_mutex_lock(&args->death_mutex);
		if (args->philos[i].meals_ate < (size_t)args->meals_amount)
		{
			pthread_mutex_unlock(&args->death_mutex);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&args->death_mutex);
			i++;
		}
	}
	assign_death_end(args);
	return (0);
}

void	*monitoring(void *input)
{
	int		i;
	t_args	*args;

	args = (t_args *)input;
	while (get_time() < args->t_start)
		ft_usleep(10, args);
	while (check_death_end(args))
	{
		i = -1;
		while (++i < args->philo_amount)
		{
			ft_usleep(5, args);
			if (check_death_end(args) == 0)
				return (NULL);
			if (check_starvation(args, &args->philos[i]) == 0
				|| check_death_end(args) == 0)
				return (NULL);
			if (args->meals_amount != -1)
			{
				if (check_meals_done(args) == 0 || check_death_end(args) == 0)
					return (NULL);
			}
		}
	}
	return (NULL);
}
