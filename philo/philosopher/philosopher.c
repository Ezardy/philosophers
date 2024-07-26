/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 06:47:02 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/26 06:48:10 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_philo.h"

void	*philosopher_base(t_philo *philo, int mode);

void	*philosopher(void *philo)
{
	return ((void *)philosopher_base((t_philo *)philo, 0));
}

int	init_philosopher_func(int *error)
{
	if (!*error)
		*error = (int)(long)philosopher_base(NULL, 1);
	return (*error);
}

int	dest_philosopher_func(int *error)
{
	if (!*error)
		*error = (int)(long)philosopher_base(NULL, 2);
	return (*error);
}