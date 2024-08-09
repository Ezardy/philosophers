/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:11:30 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/08 23:36:14 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/_types/_useconds_t.h>
#include <sys/time.h>

#include "state_codes.h"
#include "error_codes.h"
#include "philosopher/t_philo.h"
#include "remap/remap.h"

static int			log_state_base(t_philo *philo, int code, int mode);
static const char	*sel_desk(int code);
static void			auxiliary_info(const t_philo *philo);

int	log_state(t_philo *philo, int code)
{
	if (!philo->error)
		philo->error = log_state_base(philo, code, LOG_MODE);
	return (philo->error);
}

void	destroy_logger(int error)
{
	if (!error)
		log_state_base(NULL, 0, 0);
}

static int	log_state_base(t_philo *philo, int code, int mode)
{
	static pthread_mutex_t	m = PTHREAD_MUTEX_INITIALIZER;
	useconds_t				rstamp;
	size_t					stamp;

	if (mode)
	{
		philo->error = pthread_mutex_lock(&m) != 0 * LOGGER_ERR_MUT_DEAD_LOCK;
		if (!philo->error)
		{
			stamp = gettime();
			if (stamp > philo->conf->stt)
				rstamp = (useconds_t)(stamp - philo->conf->stt) / 1000;
			else
				rstamp = 0;
			printf("%i %li %s", rstamp, philo->id, sel_desk(code));
			if (mode == 3)
				auxiliary_info(philo);
			printf("\n");
			pthread_mutex_unlock(&m);
		}
	}
	else
		pthread_mutex_destroy(&m);
	return (philo && philo->error);
}

static void	auxiliary_info(const t_philo *philo)
{
	printf("; i - %li; tec - %li; ttd - %li", philo->i,
		(*philo->tec - philo->conf->stt) / 1000,
		(philo->ttd - philo->conf->stt) / 1000);
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
