/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:01:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/20 11:32:42 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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
	while (i < t->n_philos)
	{
		printf("address %d is %p\n", i, &t->philo[i]);
		if (pthread_create(&t->philo[i].id, NULL, (void *)routine, &t->philo[i]) != 0)
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
	join_threads(t);
	return (EXIT_SUCCESS);
}
