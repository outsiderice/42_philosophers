/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:16:43 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/31 22:11:43 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include "../inc/parse.h"

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
	if (philosophers(&t) == 1 || t.error == 1)
	{
		write(2, "Philosophers execution failure\n", 32);
		return (4);
	}
	return (0);
}
