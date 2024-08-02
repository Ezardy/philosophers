/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:20:55 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/02 00:23:01 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <sys/semaphore.h>
#include <sys/time.h>
#include <unistd.h>

#include "logger/state_codes.h"
#include "logger/error_codes.h"
#include "logger/logger.h"
#include "remap/remap.h"
#include "t_philo.h"

static int	die(t_philo *philo, int *error, sem_t *ds);

int	eat(t_philo *philo, size_t t, int *error, sem_t *ds)
{
	if (!(sem_wait_r(philo->s, PHILOSOPHER_ERR_BEGIN, error)
			|| log_state(philo->conf->stt, philo->id, LOG_TAKE_FORK, error)))
	{
		if (philo->conf->nop == 1)
		{
			die(philo, error, ds);
			sem_post(philo->s);
		}
		else
		{
			if (!(sem_wait_r(philo->s, PHILOSOPHER_ERR_BEGIN, error)
					|| log_state(philo->conf->stt, philo->id, LOG_TAKE_FORK,
						error)
					|| log_state(philo->conf->stt, philo->id, LOG_EAT, error)))
			{
				usleep(philo->conf->te);
				philo->ate += 1;
				philo->ttd = t + philo->conf->te + philo->conf->td;
				sem_post(philo->s);
			}
		}
		sem_post(philo->s);
	}
	return (*error || philo->ate >= philo->conf->notepme);
}

int	phsleep(t_philo *philo, size_t t, int *error, sem_t *ds)
{
	if (!log_state(philo->conf->stt, philo->id, LOG_SLEEP, error))
	{
		if (t + philo->conf->te + philo->conf->ts < philo->ttd)
			usleep(philo->conf->ts);
		else
			die(philo, error, ds);
	}
	return (*error);
}

int	think(t_philo *philo, size_t t, int *error, sem_t *ds)
{
	if (!log_state(philo->conf->stt, philo->id, LOG_THINK, error))
	{
		if (t < philo->ttd)
			safe_sleep(t);
		else
			die(philo, error, ds);
	}
	return (*error);
}

static int	die(t_philo *philo, int *error, sem_t *ds)
{
	safe_sleep(philo->ttd);
	if (!(sem_wait_r(ds, PHILOSOPHER_ERR_BEGIN, error)
			|| log_state(philo->conf->stt, philo->id, LOG_DIE, error)))
		*error = PHILOSOPHER_DIED;
	return (*error);
}
