/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 06:47:02 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/02 06:17:22 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_philo.h"

int	philosopher_base(t_philo *philo, int mode);

int	philosopher(t_philo *philo)
{
	return (philosopher_base(philo, 0));
}

int	init_philosopher_func(int *error)
{
	if (!*error)
		*error = philosopher_base(NULL, 1);
	return (*error);
}

void	dest_philosopher_func(void)
{
	philosopher_base(NULL, 2);
}
