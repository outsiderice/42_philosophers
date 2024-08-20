/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/20 10:58:21 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*routine(t_philo *philo)
{
	int	*status;

	status = &philo->status;
	printf("I'm philosopher %d\n", philo->name);
	return ((void *) status);
}
