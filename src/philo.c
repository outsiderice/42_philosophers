/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:01:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/30 17:45:37 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	join_threads(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos)
	{
		if (pthread_join(t->philo[i].id, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	finished_eating(t_table	*t)
{
	int	i;
	
	i = 0;

	while (i < t->n_philos)
	{
		pthread_mutex_lock(&t->philo[i].meals_lock);
		if (t->philo[i].n_eaten == 0)
		{
			pthread_mutex_unlock(&t->philo[i].meals_lock);
			i++;
		}
	}
	if (i == t->n_philos)
	{
		pthread_mutex_lock(&t->end_lock);
		t->end = 1;
		pthread_mutex_unlock(&t->end_lock);
		return (1);
	}
	return (0);
}

int	watch_threads(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philos && !t->end)
	{
		pthread_mutex_lock(&t->philo[i].timer_lock);
		if (t->philo[i].timer >= t->to_die)
		{
			pthread_mutex_lock(&t->end_lock);
			print_msg(&t->philo[i], "died");
			t->end = 1;
			pthread_mutex_unlock(&t->end_lock);
		}
		pthread_mutex_unlock(&t->philo[i].timer_lock);
		i++;
		if (i == t->n_philos && finished_eating(t) == 0)
			i = 0;
		usleep(250);
	}
	if (join_threads(t) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_threads(t_table *t)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&t->ready);
	while (i < t->n_philos)
	{
		if (pthread_create(&t->philo[i].id, NULL, (void *)philo_start, &t->philo[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	philosophers(t_table *t)
{
	if (create_threads(t) == 1)
	{
		destroy_all_mutex(t, t->n_philos);
		ft_free(t->philo, t->forks, 1);
		return (EXIT_FAILURE);
	}
	if (gettimeofday(&t->start, NULL) == -1)
	{
		destroy_all_mutex(t, t->n_philos);
		ft_free(t->philo, t->forks, 1);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&t->ready);
	if (watch_threads(t) == 1)
	{
		destroy_all_mutex(t, t->n_philos);
		ft_free(t->philo, t->forks, 1);
		return (EXIT_FAILURE);
	}
	printf("after watch threads and join\n");
	destroy_all_mutex(t, t->n_philos);
	ft_free(t->philo, t->forks, 0);
	printf("end of philo\n");
	return (EXIT_SUCCESS);
}
