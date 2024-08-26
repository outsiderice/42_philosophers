/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:50:24 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/26 14:06:53 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// Converts numbers contained in inital part of the string pointed by STR to int
// Returns 0 if it can't. It allows one use of + or - before the number.
int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	n;

	i = 0;
	a = 0;
	n = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		n = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = 10 * a + (str[i] - '0');
		i++;
	}
	return (n * a);
}

int	ft_free(void *arg, void *arg2, int status)
{
	free(arg);
	if (arg2)
		free(arg2);
	return (status);
}

int	ft_usleep(t_table *t, int wait)
{
	int	wait_start;
	int	time_elapsed;

	wait_start = ft_time(t);
	if (wait_start == -1)
		return (EXIT_FAILURE);
	while ("time passes")
	{
		time_elapsed = ft_time(t);
		if (time_elapsed == -1)
			return (EXIT_FAILURE);
		if (time_elapsed - wait_start >= wait)
			break ;
		usleep(1000);
	}
	return (EXIT_SUCCESS);
}

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

