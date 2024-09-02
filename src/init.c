/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:15:36 by amagnell          #+#    #+#             */
/*   Updated: 2024/09/02 10:42:16 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_philos(t_table *t)
{
	int	i;
	int	left;

	i = 0;
	while (i < t->n_philos)
	{
		left = i + 1;
		if (left >= t->n_philos)
			left = 0;
		t->philo[i].name = i + 1;
		t->philo[i].meals_left = t->meals;
		t->philo[i].r_fork = &t->forks[i];
		t->philo[i].l_fork = &t->forks[left];
		t->philo[i].t = t;
		t->philo[i].timer = 0;
		if (pthread_mutex_init(&t->philo[i].timer_lock, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	destroy_all_mutex(t_table *t, int i)
{
	pthread_mutex_destroy(&t->print);
	pthread_mutex_destroy(&t->ready);
	pthread_mutex_destroy(&t->end_lock);
	pthread_mutex_destroy(&t->meal_end);
	while (--i >= 0)
		pthread_mutex_destroy(&t->forks[i]);
}

int	init_forks(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_philos)
	{
		if (pthread_mutex_init(&t->forks[i], NULL) != 0)
		{
			destroy_all_mutex(t, i);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	init_mutex(t_table *t)
{
	if (pthread_mutex_init(&t->print, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&t->ready, NULL) != 0)
	{
		pthread_mutex_destroy(&t->print);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&t->meal_end, NULL) != 0)
	{
		pthread_mutex_destroy(&t->print);
		pthread_mutex_destroy(&t->ready);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&t->end_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&t->print);
		pthread_mutex_destroy(&t->ready);
		pthread_mutex_destroy(&t->meal_end);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&t->err, NULL) != 0)
		return (EXIT_FAILURE);
	if (init_forks(t) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_table(char **argv, t_table *t)
{
	t->n_philos = ft_atoi(argv[1]);
	t->to_die = ft_atoi(argv[2]);
	t->to_eat = ft_atoi(argv[3]);
	t->to_sleep = ft_atoi(argv[4]);
	t->meals = -1;
	if (argv[5] != NULL)
		t->meals = ft_atoi(argv[5]);
	t->philo = malloc(sizeof(t_philo) * t->n_philos);
	if (!t->philo)
		return (EXIT_FAILURE);
	t->forks = malloc(sizeof(pthread_mutex_t) * t->n_philos);
	if (!t->forks)
		return (ft_free(t->philo, NULL, EXIT_FAILURE));
	if (init_mutex(t) == 1)
		return (ft_free(t->philo, t->forks, EXIT_FAILURE));
	init_philos(t);
	return (EXIT_SUCCESS);
}
