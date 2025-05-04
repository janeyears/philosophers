/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:34:35 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/04 21:22:53 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init(t_args *args)
{
	args->is_end = false;
	args->philos = ft_calloc(args->philo_amount, sizeof(t_philo));
	if (!args->philos)
		return (1);
	args->forks = ft_calloc(args->philo_amount, sizeof(t_fork));
	if (!args->forks)
		return (free(args->philos), 1);
	args->t_start = get_time();
	if (args->t_start == 0)
		return (free(args->philos), free(args->forks), 1);
}