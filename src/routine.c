/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/26 12:29:41 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

/*
void	sleeping()
{}

void	eating()
{
	pthread_mutex_lock(&philo->r_fork);
}
*/



void	*philo_start(t_philo *philo)
{
	int	*status;
	int	exit;

	exit = EXIT_FAILURE;
	pthread_mutex_lock(&philo->t->ready);
	pthread_mutex_unlock(&philo->t->ready);
	if (philo->t->n_philos == 1)
		wait_to_die(philo);
	else
	{
		if((philo->name % 2) == 0)
		{
			if (ft_usleep(1) == 1)
				return((void *) status);
		}
	}
	exit = EXIT_SUCCESS;
	return ((void *) status);
}
