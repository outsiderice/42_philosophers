/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:16:43 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/19 22:47:37 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
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
	if (store_args() == 1)
	{
		printf("Allocation failure\n");
		return (3);
	}
	if (philosophers() == 1)
	{
		printf("Philosophers execution error\n");
		return (4);
	}
	return (0);
}
