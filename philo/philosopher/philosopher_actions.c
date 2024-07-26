/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:20:55 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/26 07:54:54 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#include "logger/state_codes.h"
#include "logger/error_codes.h"
#include "logger/logger.h"
#include "t_philo.h"
#include "remap/remap.h"

static int	die(size_t start_time, size_t td, size_t id, int *error);

int	eat(t_philo *philo, size_t t, int *error)
{
	if (!(mut_lock(philo->lm, PHILOSOPHER_ERR_MUT_DL, error)
			|| log_state(philo->conf->stt, philo->id, LOG_TAKE_FORK, error)))
	{
		if (philo->lm == philo->rm)
		{
			die(philo->conf->stt, philo->ttd, philo->id, error);
			pthread_mutex_unlock(philo->lm);
		}
		else
		{
			if (!(mut_lock(philo->rm, PHILOSOPHER_ERR_MUT_DL, error)
					|| log_state(philo->conf->stt, philo->id, LOG_TAKE_FORK,
						error)
					|| log_state(philo->conf->stt, philo->id, LOG_EAT, error)))
			{
				usleep(philo->conf->te);
				philo->ate += 1;
				philo->ttd = t + philo->conf->td;
				pthread_mutex_unlock(philo->lm);
				pthread_mutex_unlock(philo->rm);
			}
		}
	}
	return (*error || philo->ate >= philo->conf->notepme);
}

int	phsleep(t_philo *philo, size_t t, int *error)
{
	if (!log_state(philo->conf->stt, philo->id, LOG_SLEEP, error))
	{
		if (t + philo->conf->te + philo->conf->ts < philo->ttd)
			usleep(philo->conf->ts);
		else
			die(philo->conf->stt, philo->ttd, philo->id, error);
	}
	return (*error);
}

int	think(t_philo *philo, size_t t, int *error)
{
	if (!log_state(philo->conf->stt, philo->id, LOG_THINK, error))
	{
		if (t < philo->ttd)
			safe_sleep(t);
		else
			die(philo->conf->stt, philo->ttd, philo->id, error);
	}
	return (*error);
}

static int	die(size_t start_time, size_t td, size_t id, int *error)
{
	safe_sleep(td);
	if (!(*error || log_state(start_time, id, LOG_DIE, error)))
		*error = PHILOSOPHER_DIED;
	return (*error);
}
