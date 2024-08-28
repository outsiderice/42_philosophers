/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:16:43 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/28 15:56:17 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/parse.h"

void	init_philos(t_table *t)
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
		t->philo[i].n_eaten = 0;
		t->philo[i].r_fork = &t->forks[i];
		t->philo[i].l_fork = &t->forks[left];
		t->philo[i].t = t;
		i++;
	}
}

void	destroy_all_mutex(t_table *t, int i)
{
	pthread_mutex_destroy(&t->print);
	pthread_mutex_destroy(&t->ready);
	while (--i >= 0)
		pthread_mutex_destroy(&t->forks[i]);
}

int	init_mutex(t_table *t)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&t->print, NULL) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&t->ready, NULL) != 0)
	{
		pthread_mutex_destroy(&t->print);
		return (EXIT_FAILURE);
	}
	while (i < t->n_philos)
	{
		if (pthread_mutex_init(&t->forks[i], NULL) != 0)
		{
			destroy_all_mutex(t, i);
			return (EXIT_FAILURE);
		}
		i++;
	}
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

int	main(int argc, char **argv)
{
	t_table	t;

	if (argc > 6 || argc < 5)
	{
		write(2, "Wrong number of arguments\n", 27);
		return (1);
	}
	if (parse(argv) == 1)
	{
		write(2, "Invalid arguments\n", 19);
		return (2);
	}
	if (init_table(argv, &t) == 1)
	{
		write(2, "Error initializing\n", 20);
		return (3);
	}
	if (philosophers(&t) == 1 || t.error)
	{
		write(2, "Philosophers execution failure\n", 32);
		return (4);
	}
	return (0);
}
