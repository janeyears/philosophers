/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:44:33 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/12 17:54:52 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define ERR_ARGS "./philo <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> optional: <number_of_times_each_philosopher_must_eat>"
# define ERR_ALLOC "Allocation has failed"
# define ERR_ONE "There must be at least one philosopher and one meal if applicable"
# define ERR_NEG "Negative numbers are not allowed"
# define ERR_NOTINT "Input must be an integer"
# define ERR_TIME "Time values must be greater than 0"
# define ERR_OVERFLOW "Int overflow detected"
# define ERR_GETTIME "gettimeofday has failed"
# define ERR_FORKS "Forks initialization has failed"
# define ERR_PHILO "Philosopher initialization has failed"
# define ERR_MUTEX "Mutex initialization has failed"
# define ERR_THREAD_PHILO "Thread creation for philo has failed"
# define ERR_THREAD_MONITOR "Thread creation for monitor has failed"
# define ERR_JOIN "Thread join has failed"

typedef struct s_args	t_args;

typedef struct s_fork
{
	int				f_id;
	pthread_mutex_t	f_lock;
}	t_fork; 

typedef struct s_philo
{	
	t_args		*arg_info;
	int			ph_id;	
	t_fork		*first_fork;
	t_fork		*second_fork;
	bool		is_eating;
	bool		has_ate;
	size_t		t_last_meal;
	size_t		t_next_meal;
	size_t		meals_ate;
	pthread_t	t_id;
}	t_philo;

typedef struct s_args
{
	long			philo_amount;
	long			meals_amount;
	size_t			t_start;
	size_t			t_to_die;
	size_t			t_to_sleep;
	size_t			t_to_eat;
	t_philo			*philos;
	t_fork			*forks;
	bool			is_end;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	wait_fork_mutex;
	pthread_t		monitor_thread;
}	t_args;

int		parsing(t_args *args, char **av);
int		init(t_args *args);

int		start_dinner(t_args *args);
int		check_meals_done(t_args *args);
int		check_death_end(t_args *args);
void	*monitoring_philos(void *input);
void	*philo_routine(void *input);


void	error_msg(char *message);
long	ft_atol(char *str);
int		is_space(char c);
void	*ft_calloc(size_t number, size_t size);
void	ft_usleep(size_t time, t_args *args);

size_t	get_time(void);
void	print_status(t_philo *philo, char *status);
void	assign_death_end(t_args *args);
void	check_time_for_odd(t_philo *philo);

void	destroy_and_free(t_args *args);
void	wait_to_start(size_t time, t_args *args);


#endif