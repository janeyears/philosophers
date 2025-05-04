/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:44:37 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/04 19:31:31 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_args	args;
	if (ac != 5 || ac != 6)
		return(error_msg(ERR_ARGS), 0);
	args = ft_calloc(1, sizeof(t_args));
		return(error_msg(ERR_ALLOC), 1);
	if (parsing(&args, av + 1) != 0)
		return(free(args), 1);
	if (init(&args) != 0)
		return(free(args), error_msg(ERR_INIT), 1);
	if (dinner_loop (&args) != 0)
		return(clean_args(&args), 1);
	clean_args(&args);
	return (0);
}	
