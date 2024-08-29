/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/29 16:47:59 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

int	sleeping(t_philo *philo)
{
	if (print_msg(philo, "is sleeping") == 1)
		return (EXIT_FAILURE);
	if (time_passes(philo, philo->t->to_sleep) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (print_msg(philo, "has taken a fork") == 1)
		return (EXIT_FAILURE);
	if (print_msg(philo, "is thinking") == 1)
		return (EXIT_FAILURE);
	if (!pthread_mutex_lock(philo->l_fork))
		time_passes(philo, 1);
	if (print_msg(philo, "has taken a fork") == 1)
		return (EXIT_FAILURE);
	if (print_msg(philo, "is eating") == 1)
		return (EXIT_FAILURE);
	philo->timer = 0;
	if (time_passes(philo, philo->t->to_eat) == 1)
		return (EXIT_FAILURE);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	return (EXIT_SUCCESS);
}

int	philo_loop(t_philo *philo)
{
	while (!philo->t->end)
	{
		if (eating(philo) == 1)
			return (EXIT_FAILURE);
		if (sleeping(philo) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	die_alone(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (print_msg(philo, "has taken a fork") == 1)
		return (EXIT_FAILURE);
	if (time_passes(philo, philo->t->to_die) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
