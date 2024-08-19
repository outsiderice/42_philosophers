/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnell <amagnell@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:15:48 by amagnell          #+#    #+#             */
/*   Updated: 2024/08/20 00:09:55 by amagnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct s_gen
{
	int		philos;
	int		to_die;
	int		to_eat;
	int		to_sleep;
	int		meals;
	struct	s_philo	*philo;
	pthread_mutex_t	print;
}			t_gen;

// status:
// alive = 1
// dead = -1
// eaten all meals = 0
typedef struct s_philo
{
	pthread_t	*id;
	int		name;
	int		status;
	int		n_eaten;
	pthread_mutex_t	fork;
}

#endif
