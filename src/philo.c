/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:01:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/09/02 12:41:37 by amagnell         ###   ########.fr       */
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
	int	finished;

	finished = 0;
	pthread_mutex_lock(&t->meal_end);
	finished = t->finished_eating;
	pthread_mutex_unlock(&t->meal_end);
	if (finished >= t->n_philos)
	{
		pthread_mutex_lock(&t->end_lock);
		t->end = 1;
		pthread_mutex_unlock(&t->end_lock);
		return (1);
	}
	pthread_mutex_unlock(&t->meal_end);
	return (0);
}

int	watch_threads(t_table *t, int i, int stop)
{
	while (i < t->n_philos && stop != 1)
	{
		pthread_mutex_lock(&t->philo[i].timer_lock);
		if (t->philo[i].timer > t->to_die)
		{
			pthread_mutex_unlock(&t->philo[i].timer_lock);
			print_msg(&t->philo[i], "died");
			pthread_mutex_lock(&t->end_lock);
			t->end = 1;
			pthread_mutex_unlock(&t->end_lock);
			break ;
		}
		pthread_mutex_unlock(&t->philo[i].timer_lock);
		if (finished_eating(t) == 1)
			break ;
		pthread_mutex_lock(&t->err);
		stop = t->error;
		pthread_mutex_unlock(&t->err);
		if (++i == t->n_philos)
			i = 0;
		usleep(10);
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
		if (pthread_create(&t->philo[i].id, NULL, \
			(void *)philo_start, &t->philo[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	philosophers(t_table *t)
{
	if (create_threads(t) == 1)
	{
		destroy_all_mutex(t, t->n_philos, 0);
		return (ft_free(t->philo, t->forks, 1));
	}
	if (gettimeofday(&t->start, NULL) == -1)
	{
		destroy_all_mutex(t, t->n_philos, 0);
		return (ft_free(t->philo, t->forks, 1));
	}
	pthread_mutex_unlock(&t->ready);
	if (watch_threads(t, 0, 0) == 1)
	{
		destroy_all_mutex(t, t->n_philos, 0);
		return (ft_free(t->philo, t->forks, 1));
	}
	if (join_threads(t) == 1)
	{
		destroy_all_mutex(t, t->n_philos, 0);
		return (ft_free(t->philo, t->forks, 1));
	}
	destroy_all_mutex(t, t->n_philos, 0);
	ft_free(t->philo, t->forks, 0);
	return (EXIT_SUCCESS);
}
