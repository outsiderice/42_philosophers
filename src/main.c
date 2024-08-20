/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:16:43 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/20 09:22:18 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/parse.h"
#include <stdio.h>

void	init_philos(t_table *t)
{
	int	i;
	int	left;

	i = 0;
	while (i <= t->n_philos)
	{
		left = i + 1;
		if (left > t->n_philos)
			left = 0;
		t->philo[i].name = i + 1;
		t->philo[i].status = 1;
		t->philo[i].n_eaten = 0;
		t->philo[i].r_fork = t->forks[i];
		t->philo[i].l_fork = t->forks[left];
		t->philo[i].t = t;
		i++;
	}
}

int	init_mutex(t_table *t)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&t->print, NULL) != 0)
		return (EXIT_FAILURE);
	while (i < t->n_philos)
	{
		if (pthread_mutex_init(&t->forks[i], NULL) != 0)
		{
			pthread_mutex_destroy(&t->print);
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
	t->philo = malloc(sizeof(t_philo) * table->n_philos);
	if (!t_philo)
		return(EXIT_FAILURE);
	t->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);
	if (!t->forks)
		return (ft_free(t->philo, NULL, EXIT_FAILURE));
	if (init_mutex(t) == 1)
		return (ft_free(t->philo, t->forks, EXIT_FAILURE));
	init_philos(table);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_table	t;

	if (argc > 6 || argc < 5)
	{
		printf("Wrong number of arguments\n");
		return (1);
	}
	if (parse(argv) == 1)
	{
		printf("Invalid arguments\n");
		return (2);
	}
	if (init_table(argv, &t) == 1)
	{
		printf("Error initializing\n");
		return (3);
	}
	if (philosophers(&t) == 1)
	{
		printf("Philosophers execution error\n");
		return (4);
	}
	return (0);
}
