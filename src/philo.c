/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:01:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/23 12:58:22 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_time(t_philo *philo)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (EXIT_FAILURE);
	philo->now = now.tv_usec - philo->t->start.tv_usec;
	if (philo->now != 0)
		philo->now = philo->now / 1000;
	return (EXIT_SUCCESS);
}

void	print_msg(t_philo *philo, char *action)
{
	ft_time(philo);
	pthread_mutex_lock(&philo->t->print);
	printf("%ld %d %s\n",philo->now, philo->name, action);
	pthread_mutex_unlock(&philo->t->print);
}

int	join_threads(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		if (pthread_join(t->philo[i].id, (void **)&t->philo[i].status) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	create_threads(t_table *t)
{
	int	i;
	
	i = 0;
	pthread_mutex_lock(&t->ready);
	while (i < t->n_philos)
	{
		if (pthread_create(&t->philo[i].id, NULL, (void *)routine, &t->philo[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	pthread_mutex_unlock(&t->ready);
	return (EXIT_SUCCESS);
}

int	philosophers(t_table *t)
{
	if (create_threads(t) == 1)
	{
		//destroy mutexs
		ft_free(t->philo, t->forks, 1);
		return (EXIT_FAILURE);
	}
	if (gettimeofday(&t->start, NULL) == -1)
	{
		//destroy mutexs
		ft_free(t->philo, t->forks, 1);
		return (EXIT_FAILURE);
	}
	join_threads(t);
	ft_free(t->philo, t->forks, 0);
	return (EXIT_SUCCESS);
}
