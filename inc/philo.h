/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:15:48 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/20 12:01:31 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_table
{
	int		n_philos;
	int		to_die;
	int		to_eat;
	int		to_sleep;
	int		meals;
	int		end;
	struct s_philo	*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}			t_table;

// status:
// alive = 1
// dead = -1
// eaten all meals = 0
typedef struct s_philo
{
	pthread_t	id;
	int		name;
	int		status;
	int		n_eaten;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	struct s_table	*t;
}			t_philo;

/*   Philo         */
int	philosophers(t_table *t);
void	print_msg(t_philo *philo, char *action);

/*   Routine       */
void	*routine(t_philo *philo);

/*   Basic Utils   */
int	ft_atoi(const char *str);
int	ft_free(void *arg, void *arg2, int status);

#endif
