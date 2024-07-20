/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 02:21:37 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/20 08:27:17 by zanikin          ###   ########.fr       */
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
	suseconds_t		tee;
	suseconds_t		teo;
	size_t			ate;
}	t_philo;

typedef struct s_philosophers
{
	int				sdied;
	int				*fs;
	t_philo			*philos;
	const t_conf	*conf;
	pthread_mutex_t	*fms;
}	t_philosophers;
#endif
