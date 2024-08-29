/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:20:35 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/29 12:43:03 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	am_i_dead(t_philo *philo, int time_elapsed)
{
	if (time_elapsed >= philo->t->to_die)
	{
		print_msg(philo, "died");
		philo->t->end = 1;
	}
}

int	time_passes(t_philo *philo, int wait, int time_elapsed)
{
	int	wait_start;

	wait_start = ft_time(philo->t);
	if (wait_start == -1)
		return (EXIT_FAILURE);
	while(time_elapsed < philo->t->to_die)
	{
		time_elapsed = ft_time(philo->t);
		if (time_elapsed == -1)
			return (EXIT_FAILURE);
		if (time_elapsed - wait_start >= wait)
			break ;
		usleep(200);
	}
	am_i_dead(philo, time_elapsed);
	philo->timer = time_elapsed;
	return (EXIT_FAILURE);
}
