/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 09:40:33 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/21 15:55:49 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

void	*routine(t_philo *philo)
{
	int	*status;

	status = &philo->status;
	ft_time(philo);
	print_msg(philo, "exists");
	return ((void *) status);
}
