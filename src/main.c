/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:44:37 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/07 22:39:19 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	int i = 0;
	t_args	*args;
	if (ac != 5 && ac != 6)
		return(error_msg(ERR_ARGS), 0);
	args = ft_calloc(1, sizeof(t_args));
	if (!args)
		return(error_msg(ERR_ALLOC), 1);
	if (parsing(args, av + 1) != 0)
		return(free(args), 1);
	if (init(args) != 0)
		return(free(args), 1);
	while (i < args->philo_amount)
	{
		printf("Philosophers stats: %d %zu %zu %zu %d\n", args->philos[i].ph_id,
			args->philos[i].t_last_meal, args->philos[i].t_next_meal,
			args->philos[i].meals_ate, args->philos[i].has_ate);
		i++;
	}
	if (start_dinner (args) != 0)
		return(destroy_and_free(args), 1);
	destroy_and_free(args);
	return (0);
}	
