/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:59:36 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/14 15:55:06 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
}

static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->first_fork->f_lock);
	pthread_mutex_unlock(&philo->second_fork->f_lock);
}

static void	try_to_eat(t_philo *philo)
{
	pickup_forks(philo);
	pthread_mutex_lock(&philo->arg_info->death_mutex);
	philo->t_last_meal = get_time();
	philo->is_eating = true;
	philo->meals_ate += 1;
	pthread_mutex_unlock(&philo->arg_info->death_mutex);
	print_status(philo, "is eating");
	philo->t_next_meal = philo->t_last_meal + philo->arg_info->t_to_eat * 2 + 1;
	philo->has_ate = true;
	smart_sleep(philo, 1);
	release_forks(philo);
	philo->is_eating = false;
}

void	*philo_routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	while (get_time() < philo->arg_info->t_start)
		ft_usleep(10, philo->arg_info);
	if (philo->arg_info->philo_amount == 1)
		return (single_lunch(philo), NULL);
	if (philo->ph_id % 2 == 1)
		ft_usleep(10, philo->arg_info);
	while (check_death_end(philo->arg_info))
	{
		check_time_for_odd(philo);
		if (philo->has_ate == false && check_death_end(philo->arg_info))
			try_to_eat(philo);
		if (philo->has_ate == true && check_death_end(philo->arg_info))
		{
			philo->has_ate = false;
			print_status(philo, "is sleeping");
			smart_sleep(philo, 0);
			print_status(philo, "is thinking");
		}
	}
	return (NULL);
}
