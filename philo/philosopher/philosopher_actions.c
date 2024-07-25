/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:20:55 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/25 07:17:47 by zanikin          ###   ########.fr       */
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

static int	die(size_t td, size_t id, int *error);

int	eat(t_philo *philo, size_t t, int *error)
{
	if (!(mut_lock(philo->lm, PHILOSOPHER_ERR_MUT_DL, error)
			|| log_state(philo->id, LOG_TAKE_FORK, error)))
	{
		if (philo->lm == philo->rm)
		{
			die(philo->ttd, philo->id, error);
			pthread_mutex_unlock(philo->lm);
		}
		else
		{
			if (!(mut_lock(philo->rm, PHILOSOPHER_ERR_MUT_DL, error)
					|| log_state(philo->id, LOG_TAKE_FORK, error)
					|| log_state(philo->id, LOG_EAT, error)))
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
	if (!log_state(philo->id, LOG_SLEEP, error))
	{
		if (t + philo->conf->te + philo->conf->ts < philo->ttd)
			usleep(philo->conf->ts);
		else
			die(philo->ttd, philo->id, error);
	}
	return (*error);
}

int	think(t_philo *philo, size_t t, int *error)
{
	size_t	rem;

	if (!log_state(philo->id, LOG_THINK, error))
	{
		if (t < philo->ttd)
			safe_sleep(t);
		else
			die(philo->ttd, philo->id, error);
		if (philo->tee - philo->teo + philo->conf->te > philo->conf->ts)
			rem = philo->tee + philo->conf->te - philo->teo - philo->conf->ts;
		else
			rem = 0;
		philo->teo = philo->teo + philo->conf->ts + rem;
		philo->tee = philo->teo + philo->conf->te;
	}
	return (*error);
}

static int	die(size_t td, size_t id, int *error)
{
	safe_sleep(td);
	if (!(*error || log_state(id, LOG_DIE, error)))
		*error = PHILOSOPHER_DIED;
	return (*error);
}
