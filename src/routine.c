/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:59:36 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/11 23:19:27 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	long_dream(t_philo *philo, int action)
{
	int	sleep_time;
	int	rest;

	if (philo->arg_info->t_to_die >= 60)
		sleep_time = philo->arg_info->t_to_die / 10;
	else
		sleep_time = philo->arg_info->t_to_die;
	if (action == 0)
		rest = philo->arg_info->t_to_eat;
	else
		rest = philo->arg_info->t_to_sleep;
	while (check_death_end(philo->arg_info) && rest > 0)
	{
		ft_usleep(sleep_time, philo->arg_info);
		rest -= sleep_time;
		if (rest < sleep_time)
			sleep_time = rest;
	}
}

static void	single_lunch(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->f_lock);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->arg_info->t_to_die, philo->arg_info);
}

static void	pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->f_lock);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->f_lock);
	print_status(philo, "has taken a fork");
	philo->is_eating = true;
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->first_fork->f_lock);
	pthread_mutex_unlock(&philo->second_fork->f_lock);
}

static void	try_to_eat(t_philo *philo)
{
	pickup_forks(philo);
	print_status(philo, "is eating");
	philo->t_last_meal = get_time();
	philo->t_next_meal = philo->t_last_meal + philo->arg_info->t_to_eat * 2 + 1;
	philo->meals_ate += 1;
	long_dream(philo, 0);
	release_forks(philo);
	philo->is_eating = false;
}

void	*philo_routine(void *input)
{
	t_philo *philo;

	philo = (t_philo *)input;
	wait_to_start(philo->arg_info->t_start, philo->arg_info);
	if (philo->arg_info->philo_amount == 1)
		return(single_lunch(philo), NULL);
	if (philo->ph_id % 2 == 1)
		ft_usleep(1, philo->arg_info); 
		while (check_death_end(philo->arg_info))
		{
			philo->has_ate = false;
			check_time_for_odd(philo);
			if (philo->has_ate == false && check_death_end(philo->arg_info))
				try_to_eat(philo);
			if (check_death_end(philo->arg_info))
			{
				print_status(philo, "is sleeping");
				long_dream(philo, 1);
				print_status(philo, "is thinking");
			}
		}
	return(NULL);
}
