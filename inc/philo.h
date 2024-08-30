/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:15:48 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/30 16:01:14 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_table
{
	int				n_philos;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				meals;
	int				end;
	int				error;
	struct s_philo	*philo;
	struct timeval	start;
	pthread_mutex_t	print;
	pthread_mutex_t	ready;
	pthread_mutex_t	*forks;
	pthread_mutex_t	end_lock;
}	t_table;

typedef struct s_philo
{
	pthread_t		id;
	int				name;
	int				n_eaten;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_table	*t;
	int				timer;
	pthread_mutex_t	timer_lock;
}	t_philo;

/*   Main          */
void	destroy_all_mutex(t_table *t, int i);

/*   Philo         */
int		philosophers(t_table *t);

/*   Routine       */
void	*philo_start(t_philo *philo);

/*   Philo utils   */
int		time_passes(t_philo *philo, int wait);
int		ft_time(t_table *t);
int		print_msg(t_philo *philo, char *action);

/*   Utils         */
int		ft_atoi(const char *str);
int		ft_free(void *arg, void *arg2, int status);

#endif
