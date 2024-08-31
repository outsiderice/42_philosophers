/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/31 17:10:19 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

void	sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping")
	time_passes(philo, philo->t->to_sleep)
}

int	eating(t_philo *philo)
{
	int	wait_start;

	print_msg(philo, "is thinking")
	wait_start = ft_time(philo->t);
	pthread_mutex_lock(philo->r_fork);
	philo->timer = philo->timer + (ft_time(philo->t) - wait_start);
	print_msg(philo, "has taken a fork")
	wait_start = ft_time(philo->t);
	pthread_mutex_lock(philo->l_fork);
	philo->timer = philo->timer + (ft_time(philo->t) - wait_start);
	print_msg(philo, "has taken a fork")
	print_msg(philo, "is eating")
	philo->timer = 0;
	time_passes(philo, philo->t->to_eat)
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->meals_left--;
	if (philo->meals_left == 0)
	{
		pthread_mutex_lock(&philo->t->meal_end);
		philo->t->finished_eating++;
		pthread_mutex_unlock(&philo->t->meal_end);
	}
	return (EXIT_SUCCESS);
}

int	philo_loop(t_philo *philo)
{
	while (!philo->t->end)
	{
		if (eating(philo) == 1)
			return (EXIT_FAILURE);
		if (philo->meals_left == 0)
			break ;
		if (sleeping(philo) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	die_alone(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_msg(philo, "has taken a fork")
	time_passes(philo, philo->t->to_die)
}

void	*philo_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->t->ready);
	pthread_mutex_unlock(&philo->t->ready);
	if (philo->t->n_philos == 1)
	{
		if (die_alone(philo) == 1)
			return (NULL);
	}
	else
	{
		philo->timer = 0;
		if ((philo->name % 2) == 0)
		{
			if (time_passes(philo, 1) == 1)
				return (NULL);
		}
		if (philo_loop(philo) == 1)
			return (NULL);
	}
	return (NULL);
}
