/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 02:21:37 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/06 06:31:44 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PHILO_H
# define T_PHILO_H
# include <sys/time.h>
# include <pthread.h>

# include "config.h"

typedef struct s_philo
{
	pthread_mutex_t	*lm;
	pthread_mutex_t	*rm;
	const t_conf	*conf;
	size_t			i;
	size_t			id;
	size_t			te[2];
	size_t			*tec;
	size_t			ttd;
	size_t			ate;
}	t_philo;

typedef struct s_philosophers
{
	int				*fs;
	t_philo			*philos;
	t_conf			*conf;
	pthread_mutex_t	*fms;
}	t_philosophers;
#endif
