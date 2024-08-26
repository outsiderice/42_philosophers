/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:01:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/26 12:32:55 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_time(t_table *t)
{
	struct timeval	time;
	int		now;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	now = (time.tv_sec - t->start.tv_sec) * 1000
		+ (time.tv_usec - t->start.tv_usec) / 1000;
	return (now);
}

int	print_msg(t_philo *philo, char *action)
{
	int	now;

	now = ft_time(philo);
	if (now == -1)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&philo->t->print);
	if (!philo->t->any_dead)
		printf("%d %d %s\n",now, philo->name, action);
	pthread_mutex_unlock(&philo->t->print);
	return (EXIT_SUCCESS);
}

int	join_threads(t_table *t)
{
	int	i;
	int	*return_val;

	i = 0;
	while (i < t->n_philos)
	{
		if (pthread_join(t->philo[i].id, (void **)return_val) != 0 || \
				*return_val == 1)
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
	pthread_mutex_unlock(&t->ready);
	//watch_threads(t);
	join_threads(t);
	ft_free(t->philo, t->forks, 0);
	return (EXIT_SUCCESS);
}
