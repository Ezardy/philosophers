/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 02:21:37 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/31 15:36:40 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PHILO_H
# define T_PHILO_H
# include <sys/semaphore.h>
# include <sys/time.h>
# include <pthread.h>

# include "config.h"

typedef struct s_philo
{
	sem_t			*s;
	const t_conf	*conf;
	size_t			i;
	size_t			id;
	size_t			tee;
	size_t			teo;
	size_t			ttd;
	size_t			ate;
}	t_philo;

typedef struct s_philosophers
{
	int				*fs;
	t_philo			*philos;
	t_conf			*conf;
}	t_philosophers;
#endif
