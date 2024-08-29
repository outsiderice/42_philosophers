/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:20:35 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/29 15:05:57 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_time(t_table *t)
{
	struct timeval	time;
	int				now;

	if (gettimeofday(&time, NULL) == -1)
	{
		pthread_mutex_lock(&t->end_lock);
		t->end = 2;
		t->error = 1;
		pthread_mutex_unlock(&t->end_lock);
		return (-1);
	}
	now = (time.tv_sec - t->start.tv_sec) * 1000
		+ (time.tv_usec - t->start.tv_usec) / 1000;
	return (now);
}

int	print_msg(t_philo *philo, char *action)
{
	int	now;

	now = ft_time(philo->t);
	if (now == -1)
		return (EXIT_FAILURE);
	pthread_mutex_lock(&philo->t->print);
	pthread_mutex_lock(&philo->t->end_lock);
	if (!philo->t->end)
		printf("%d %d %s\n", now, philo->name, action);
	pthread_mutex_unlock(&philo->t->end_lock);
	pthread_mutex_unlock(&philo->t->print);
	return (EXIT_SUCCESS);
}

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
	while (time_elapsed < philo->t->to_die)
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
