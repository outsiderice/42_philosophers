/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:01:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/26 16:34:28 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	join_threads(t_table *t)
{
	int	i;
	int	*return_val;

	i = 0;
	while (i < t->n_philos)
	{
		if (pthread_join(t->philo[i].id, (void **)return_val) != 0 || \
				!t->philo[i].success)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
void	watch_threads(t_table *t)
{
}
 */

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
	//destroy_all
	ft_free(t->philo, t->forks, 0);
	return (EXIT_SUCCESS);
}
