/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 02:21:37 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/08 07:01:01 by zanikin          ###   ########.fr       */
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
	size_t			te[2];
	size_t			*tec;
	size_t			ttd;
	size_t			ate;
	int				error;
}	t_philo;
#endif
