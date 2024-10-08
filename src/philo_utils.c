/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:20:35 by amagnell          #+#    #+#             */
/*   Updated: 2024/09/05 20:17:02 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	die_alone(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_msg(philo, "has taken a fork");
	time_passes(philo, philo->t->to_die + 1);
}

int	ft_time(t_table *t)
{
	struct timeval	time;
	int				now;

	if (gettimeofday(&time, NULL) == -1)
	{
		pthread_mutex_lock(&t->end_lock);
		t->end = 1;
		pthread_mutex_unlock(&t->end_lock);
		pthread_mutex_lock(&t->err);
		t->error = 1;
		pthread_mutex_unlock(&t->err);
		return (-1);
	}
	now = (time.tv_sec - t->start.tv_sec) * 1000
		+ (time.tv_usec - t->start.tv_usec) / 1000;
	return (now);
}

void	print_msg(t_philo *philo, char *action)
{
	int	now;
	int	stop;

	pthread_mutex_lock(&philo->t->print);
	stop = 0;
	now = ft_time(philo->t);
	if (now == -1)
	{
		pthread_mutex_unlock(&philo->t->print);
		return ;
	}
	pthread_mutex_lock(&philo->t->end_lock);
	stop = philo->t->end;
	pthread_mutex_unlock(&philo->t->end_lock);
	if (stop != 1)
		printf("%d %d %s\n", now, philo->name, action);
	pthread_mutex_unlock(&philo->t->print);
}

void	time_passes(t_philo *philo, int wait)
{
	int	wait_start;
	int	now;

	wait_start = ft_time(philo->t);
	if (wait_start == -1)
		return ;
	while ("time passes")
	{
		now = ft_time(philo->t);
		if (now == -1)
			return ;
		pthread_mutex_lock(&philo->t->end_lock);
		if (now - wait_start >= wait || philo->t->end == 1)
			break ;
		pthread_mutex_unlock(&philo->t->end_lock);
		usleep(100);
	}
		pthread_mutex_unlock(&philo->t->end_lock);
}
