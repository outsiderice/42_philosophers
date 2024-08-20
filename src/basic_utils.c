/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 00:50:24 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/20 08:26:43 by amagnell         ###   ########.fr       */
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

int	ft_free(void *arg, void *arg2 int status)
{
	free(arg);
	if (arg2)
		free(arg2);
	return (status);
}
