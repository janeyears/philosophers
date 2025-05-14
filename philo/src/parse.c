/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:44:40 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/14 15:26:30 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	validate_for_pos_int(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (is_space(av[i][j]))
			j++;
		if (av[i][j] == '+')
			j++;
		else if (av[i][j] == '-')
			return (error_msg(ERR_NEG), 1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (error_msg(ERR_NOTINT), 1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_args_overflow(t_args *args)
{
	if (args->philo_amount > INT_MAX || args->meals_amount > INT_MAX
		|| args->t_to_die > INT_MAX || args->t_to_eat > INT_MAX
		|| args->t_to_sleep > INT_MAX)
		return (1);
	else
		return (0);
}

static void	parse_numbers(t_args *args, char **av)
{
	long	philo_amount;
	long	meals_amount;
	long	t_to_die;
	long	t_to_eat;
	long	t_to_sleep;

	philo_amount = ft_atol(av[0]);
	t_to_die = ft_atol(av[1]);
	t_to_eat = ft_atol(av[2]);
	t_to_sleep = ft_atol(av[3]);
	if (av[4])
	{
		meals_amount = ft_atol(av[4]);
		args->meals_amount = (size_t)meals_amount;
	}
	args->philo_amount = (size_t)philo_amount;
	args->t_to_die = (size_t)t_to_die;
	args->t_to_eat = (size_t)t_to_eat;
	args->t_to_sleep = (size_t)t_to_sleep;
}

int	parsing(t_args *args, char **av)
{
	args->meals_amount = -1;
	if (validate_for_pos_int(av) != 0)
		return (1);
	parse_numbers(args, av);
	if (args->philo_amount == 0 || args->meals_amount == 0)
		return (error_msg(ERR_ONE), 1);
	if (args->t_to_die < 1 || args->t_to_eat < 1
		|| args->t_to_sleep < 1)
		return (error_msg(ERR_TIME), 1);
	if (check_args_overflow(args) != 0)
		return (error_msg(ERR_OVERFLOW), 1);
	return (0);
}
