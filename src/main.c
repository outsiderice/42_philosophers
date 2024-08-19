/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:16:43 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/19 21:38:59 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc > 6 || argc < 5)
	{
		printf("Wrong number of arguments\n");
		return (2);
	}
	printf("This is philosophers\n");
	return (0);
}
