/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/21 18:12:08 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

/*
void	ft_sleep()
{}

void	ft_eat()
{
	if ((philo->name % 2) == 0)
		usleep(200);
	pthread_mutex_lock(&philo->r_fork);
}
*/

void	*routine(t_philo *philo)
{
	int	*status;

	pthread_mutex_lock(&philo->t->ready);
	pthread_mutex_unlock(&philo->t->ready);
	status = &philo->status;
	//ft_eat(philo);
	//ft_sleep(philo);
	return ((void *) status);
}
