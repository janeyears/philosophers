/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:35 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/15 14:11:37 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_forks(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_amount)
	{
		args->forks[i].f_id = i + 1;
		if (pthread_mutex_init(&args->forks[i].f_lock, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	setup_fork_order(t_philo *philo, t_args *args)
{
	if (philo->ph_id % 2 == 0)
	{
		philo->first_fork = &args->forks[philo->ph_id - 1];
		philo->second_fork = &args->forks[philo->ph_id % args->philo_amount];
	}
	else
	{
		philo->first_fork = &args->forks[philo->ph_id % args->philo_amount];
		philo->second_fork = &args->forks[philo->ph_id - 1];
	}
}

static void	init_philos(t_args *args)
{
	int	i;

	i = 0;
	while (i < args->philo_amount)
	{
		args->philos[i].arg_info = args;
		args->philos[i].ph_id = i + 1;
		args->philos[i].is_eating = false;
		args->philos[i].has_ate = false;
		args->philos[i].meals_ate = 0;
		args->philos[i].t_last_meal = args->t_start;
		args->philos[i].t_next_meal = args->t_start;
		setup_fork_order(&args->philos[i], args);
		i++;
	}
}

static int	init_mutex(t_args *args)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&args->print_mutex, NULL) != 0)
	{
		while (i < args->philo_amount)
		{
			pthread_mutex_destroy(&args->forks[i].f_lock);
			i++;
		}
		return (1);
	}
	if (pthread_mutex_init(&args->death_mutex, NULL) != 0)
	{
		{
			while (i < args->philo_amount)
			{
				pthread_mutex_destroy(&args->forks[i].f_lock);
				i++;
			}
			pthread_mutex_destroy(&args->print_mutex);
			return (1);
		}
	}
	return (0);
}

int	init(t_args *args)
{
	args->is_end = false;
	args->philos = ft_calloc(args->philo_amount, sizeof(t_philo));
	if (!args->philos)
		return (error_msg(ERR_ALLOC), 1);
	args->forks = ft_calloc(args->philo_amount, sizeof(t_fork));
	if (!args->forks)
		return (free(args->philos), error_msg(ERR_ALLOC), 1);
	if (init_forks(args) != 0)
		return (free(args->philos), free(args->forks), error_msg(ERR_FORKS), 1);
	args->t_start = get_time();
	init_philos(args);
	if (init_mutex(args) != 0)
		return (free(args->philos), free(args->forks), error_msg(ERR_MUTEX), 1);
	return (0);
}
