/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:11:30 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/06 06:54:49 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

#include "state_codes.h"
#include "error_codes.h"
#include "philosopher/t_philo.h"
#include "remap/remap.h"

static int			log_state_base(t_philo *philo, int code, int mode);
static const char	*sel_desk(int code);

int	log_state(t_philo *philo, int code, int *error)
{
	if (!*error)
		*error = log_state_base(philo, code, LOG_MODE);
	return (*error);
}

int	init_logger(int *error)
{
	if (!*error)
		*error = log_state_base(NULL, 0, 1);
	return (*error);
}

int	destroy_logger(int *error)
{
	if (!*error)
		*error = log_state_base(NULL, 0, 2);
	return (*error);
}

static int	log_state_base(t_philo *philo, int code, int mode)
{
	int						error;
	static pthread_mutex_t	m;

	if (mode == 1)
		error = pthread_mutex_init(&m, NULL) != 0 * LOGGER_ERR_MEM_ALLOC;
	else if (mode == 2)
		error = pthread_mutex_destroy(&m) != 0 * LOGGER_ERR_MUT_BUSY;
	else
	{
		error = pthread_mutex_lock(&m) != 0 * LOGGER_ERR_MUT_DEAD_LOCK;
		if (!error)
		{
			printf("%li %li %s", (gettime() - philo->conf->stt) / 1000,
				philo->id, sel_desk(code));
			if (mode == 3)
				printf("; i - %li; tec - %li; ttd - %li", philo->i,
					(*philo->tec - philo->conf->stt) / 1000,
					(philo->ttd - philo->conf->stt) / 1000);
			printf("\n");
			pthread_mutex_unlock(&m);
		}
	}
	return (error);
}

static const char	*sel_desk(int code)
{
	const char				*desk;

	if (code == LOG_TAKE_FORK)
		desk = LOG_TAKE_FORK_DESK;
	else if (code == LOG_EAT)
		desk = LOG_EAT_DESK;
	else if (code == LOG_SLEEP)
		desk = LOG_SLEEP_DESK;
	else if (code == LOG_THINK)
		desk = LOG_THINK_DESK;
	else
		desk = LOG_DIE_DESK;
	return (desk);
}
