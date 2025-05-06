/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:59:36 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/06 15:59:53 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void single_lunch(t_philo *philo)
{
	print_status(philo, "has taken a fork");
	ft_usleep(philo->arg_info->t_to_die);
}

static void	pickup_forks(t_philo *philo)
{
	
}
static void	try_to_eat(t_philo *philo)
{
	
}

static void	after_meal(t_philo *philo)
{
	
}

void	philo_routine(void *input)
{
	t_philo *philo;

	philo = (t_philo *)input;
	if (philo->arg_info->philo_amount == 1)
		return(single_lunch(philo), NULL);
	if (philo->ph_id % 2 == 1)
		ft_usleep(10);
	while (1)
	{
		if (check_death_end(philo->arg_info) == 0)
			return (NULL);
		check_time_for_odd(philo);
		if (philo->has_ate == false && check_death_end(philo->arg_info))
			try_to_eat(philo);
		if (philo->has_ate == true && check_death_end(philo->arg_info))
			after_meal(philo);
	}
	return(NULL);
}