/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/28 16:12:49 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>
/*
int	sleeping(t_philo *philo)
{
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);

	pthread_mutex_lock(&philo->l_fork);
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
*/
int	wait_to_die(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (print_msg(philo, "has taken a fork") == 1)
		return (EXIT_FAILURE);
	if (time_passes(philo->t, philo->t->to_die) == 1)
		return (EXIT_FAILURE);
	if (print_msg(philo, "has died") == 1)
		return (EXIT_FAILURE);
	philo->t->end = 1;
	return (EXIT_SUCCESS);
}

void	*philo_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->t->ready);
	pthread_mutex_unlock(&philo->t->ready);
	if (philo->t->n_philos == 1)
	{
		if (wait_to_die(philo) == 1)
			return (NULL);
	}
/*
	else
	{
		if ((philo->name % 2) == 0)
		{
			if (time_passes(philo->t, 1) == 1)
				return ;
		}
		if (philo_loop(philo) == 1)
			return ;
	}
*/
	return (NULL);
}
