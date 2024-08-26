/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:15:48 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/26 13:21:00 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

typedef struct s_table
{
	int		n_philos;
	int		to_die;
	int		to_eat;
	int		to_sleep;
	int		meals;
	int		any_dead;
	struct s_philo	*philo;
	struct timeval	start;
	pthread_mutex_t	print;
	pthread_mutex_t	ready;
	pthread_mutex_t	*forks;
}			t_table;

typedef struct s_philo
{
	pthread_t	id;
	int		name;
	int		n_eaten;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_table	*t;
	int		success;
}			t_philo;

/*   Philo         */
int	philosophers(t_table *t);

/*   Routine       */
void	*philo_start(t_philo *philo);

/*   Utils   */
int	ft_atoi(const char *str);
int	ft_free(void *arg, void *arg2, int status);
int	ft_usleep(t_table *t, int wait);
int	ft_time(t_table *t);
void	print_msg(t_philo *philo, char *action);

#endif
