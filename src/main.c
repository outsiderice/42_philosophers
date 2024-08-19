/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:16:43 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/20 00:27:31 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/parse.h"
#include <stdio.h>

void	store_args(char **argv, t_gen *info)
{
	info->philos = ft_atoi(argv[1]);
	info->to_die = ft_atoi(argv[2]);
	info->to_eat = ft_atoi(argv[3]);
	info->to_sleep = ft_atoi(argv[4]);
	info->meals = -1;
	if (argv[5] != NULL)
		info->meals = ft_atoi(argv[5]);
	info->philo = NULL;
}

int	main(int argc, char **argv)
{
	t_gen	info;

	info = NULL;
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
	store_args(argv, &info);
	/*
	if (philosophers() == 1)
	{
		printf("Philosophers execution error\n");
		return (3);
	}*/
	return (0);
}
