/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/26 14:16:44 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

/*
int	sleeping()
{}

int	eating()
{
	pthread_mutex_lock(&philo->r_fork);
}
*/

int	philo_loop(t_philo *philo)
{
	while(philo->)
	{
		if (eating(philo) == 1)
			return (EXIT_FAILURE);
		if (sleeping(philo) == 1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	*philo_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->t->ready);
	pthread_mutex_unlock(&philo->t->ready);
	if (philo->t->n_philos == 1)
	{
		if (wait_to_die(philo) == 1)
			return ;
	}
	else
	{
		if((philo->name % 2) == 0)
		{
			if (ft_usleep(1) == 1)
				return ;
		}
		if (philo_loop(philo) == 1)
			return ;
	}
	philo->success = 1;
	return ;
}
