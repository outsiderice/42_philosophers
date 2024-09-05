/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 19:15:36 by amagnell          #+#    #+#             */
/*   Updated: 2024/09/05 12:53:44 by amagnell         ###   ########.fr       */
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
		t->philo[i].time_of_death = t->to_die;
		i++;
	}
	return (EXIT_SUCCESS);
}

void	destroy_all_mutex(t_table *t, int i, int count, int j)
{
	pthread_mutex_destroy(&t->print);
	pthread_mutex_destroy(&t->ready);
	if (count == 2)
		return ;
	pthread_mutex_destroy(&t->meal_end);
	if (count == 3)
		return ;
	pthread_mutex_destroy(&t->end_lock);
	if (count == 4)
		return ;
	pthread_mutex_destroy(&t->err);
	while (--i >= 0)
		pthread_mutex_destroy(&t->forks[i]);
	if (count == 5)
		return ;
	while (--j >= 0)
		pthread_mutex_destroy(&t->philo[j].d_lock);
}

int	init_philo_mutex(t_table *t)
{
	int	i;

	i = -1;
	while (++i < t->n_philos)
	{
		if (pthread_mutex_init(&t->forks[i], NULL) != 0)
		{
			destroy_all_mutex(t, i, 5, 0);
			return (EXIT_FAILURE);
		}
	}
	i = -1;
	while (++i < t->n_philos)
	{
		if (pthread_mutex_init(&t->philo[i].d_lock, NULL) != 0)
		{
			destroy_all_mutex(t, t->n_philos, 0, i);
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
		destroy_all_mutex(t, 0, 2, 0);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&t->end_lock, NULL) != 0)
	{
		destroy_all_mutex(t, 0, 3, 0);
		return (EXIT_FAILURE);
	}
	if (pthread_mutex_init(&t->err, NULL) != 0)
	{
		destroy_all_mutex(t, 0, 4, 0);
		return (EXIT_FAILURE);
	}
	if (init_philo_mutex(t) == 1)
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
	t->finished_eating = 0;
	if (t->n_philos < 0 || t->to_die < 0 || t->to_eat < 0 || t->to_sleep < 0)
		return (EXIT_FAILURE);
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
