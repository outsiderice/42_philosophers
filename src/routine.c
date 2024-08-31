/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/31 23:22:02 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

void	sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	time_passes(philo, philo->t->to_sleep);
	usleep(10);
}

void	thinking(t_philo *philo)
{
	int	wait_start;

	print_msg(philo, "is thinking");
	wait_start = ft_time(philo->t);
	if (philo->name == philo->t->n_philos)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->timer_lock);
	philo->timer = philo->timer + (ft_time(philo->t) - wait_start);
	pthread_mutex_unlock(&philo->timer_lock);
	usleep(10);
	print_msg(philo, "has taken a fork");
	wait_start = ft_time(philo->t);
	if (philo->name == philo->t->n_philos)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->timer_lock);
	philo->timer = philo->timer + (ft_time(philo->t) - wait_start);
	pthread_mutex_unlock(&philo->timer_lock);
	usleep(10);
	print_msg(philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->timer_lock);
	philo->timer = 0;
	pthread_mutex_unlock(&philo->timer_lock);
	time_passes(philo, philo->t->to_eat);
	usleep(10);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	philo->meals_left--;
	if (philo->meals_left == 0)
	{
		pthread_mutex_lock(&philo->t->meal_end);
		philo->t->finished_eating++;
		pthread_mutex_unlock(&philo->t->meal_end);
	}
}

void	philo_loop(t_philo *philo)
{
	int	stop;

	stop = 0;
	while (stop != 1)
	{
		thinking(philo);
		eating(philo);
		if (philo->meals_left == 0)
			break ;
		sleeping(philo);
		pthread_mutex_lock(&philo->t->end_lock);
		stop = philo->t->end;
		pthread_mutex_unlock(&philo->t->end_lock);
	}
}

void	*philo_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->t->ready);
	pthread_mutex_unlock(&philo->t->ready);
	if (philo->t->n_philos == 1)
	{
		die_alone(philo);
		return (NULL);
	}
	else
	{
		pthread_mutex_lock(&philo->timer_lock);
		philo->timer = 0;
		pthread_mutex_unlock(&philo->timer_lock);
		if ((philo->name % 2) == 0)
			time_passes(philo, 1);
		philo_loop(philo);
	}
	return (NULL);
}
