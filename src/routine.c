/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/09/04 09:09:00 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

void	sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	time_passes(philo, philo->t->to_sleep);
	time_passes(philo, 1);
}

void	thinking(t_philo *philo, int even)
{
	print_msg(philo, "is thinking");
	if (philo->name == philo->t->n_philos && even == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	print_msg(philo, "has taken a fork");
	print_msg(philo, "has taken a fork");
}

void	eating(t_philo *philo, int even)
{
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->d_lock);
	philo->time_of_death = ft_time(philo->t) + philo->t->to_die;
	pthread_mutex_unlock(&philo->d_lock);
	time_passes(philo, philo->t->to_eat);
	if (philo->name == philo->t->n_philos && even == 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	if (philo->t->meals > 0 && philo->meals_left > 0)
	{
		philo->meals_left--;
		if (philo->meals_left == 0)
		{
			pthread_mutex_lock(&philo->t->meal_end);
			philo->t->finished_eating++;
			pthread_mutex_unlock(&philo->t->meal_end);
		}
	}
}

void	philo_loop(t_philo *philo)
{
	int	stop;
	int	even;

	stop = 0;
	even = 0;
	if (philo->t->n_philos % 2 == 0)
		even = 1;
	while (stop != 1)
	{
		thinking(philo, even);
		eating(philo, even);
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
		if ((philo->name % 2) == 1)
			time_passes(philo, 1);
		philo_loop(philo);
	}
	return (NULL);
}
