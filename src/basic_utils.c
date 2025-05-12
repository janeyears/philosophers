/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:44:43 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/12 17:27:16 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_msg(char *message)
{
	printf("%s\n", message);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

long	ft_atol(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}

void	*ft_calloc(size_t number, size_t size)
{
	void	*ptr;
	size_t	bytes;
	size_t	i;

	bytes = number * size;
	if (size == 0)
		return (NULL);
	if (size && ((bytes / size) != number))
		return (NULL);
	ptr = malloc(bytes);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < bytes)
	{
		((char *)ptr)[i] = '\0';
		i++;
	}
	return (ptr);
}

void	print_status(t_philo *philo, char *status)
{
	size_t	time;

	time = get_time() - philo->arg_info->t_start;
	pthread_mutex_lock(&philo->arg_info->death_mutex);
	if (philo->arg_info->is_end == true)
	{
		pthread_mutex_unlock(&philo->arg_info->death_mutex);
		return ;
	}
	printf("%zu %d %s\n",time, philo->ph_id, status);
	pthread_mutex_unlock(&philo->arg_info->death_mutex);
}
