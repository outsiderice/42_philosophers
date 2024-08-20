/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:01:21 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/20 09:24:48 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_threads(t_table *t)
{
	int	i;
	
	i = 0;
	while (i < t->n_philos)
	{
		if (pthread_create(&t->philos[i].id, NULL, &routine, &t->philos[i]) != 0)
			return (EXIT_FAILURE);
		i++;
	}
}

int	philosophers(t_table *t)
{
	if (create_threads(t) == 1)
	{
		//destroy mutexs
		ft_free(t->philo, t->forks, 1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
