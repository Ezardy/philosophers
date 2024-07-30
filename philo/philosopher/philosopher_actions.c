/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:20:55 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/29 07:23:43 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

#include "logger/state_codes.h"
#include "logger/error_codes.h"
#include "logger/logger.h"
#include "remap/remap.h"
#include "t_philo.h"
#include "t_state.h"

static int	die(t_philo *philo, int *error, t_state *state);

int	eat(t_philo *philo, size_t t, int *error, t_state *state)
{
	if (!(mut_lock(philo->lm, PHILOSOPHER_ERR_MUT_DL, error)
			|| log_state(philo->conf->stt, philo->id, LOG_TAKE_FORK, error)))
	{
		if (philo->lm == philo->rm)
		{
			die(philo, error, state);
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
				philo->ttd = t + philo->conf->te + philo->conf->td;
				pthread_mutex_unlock(philo->lm);
				pthread_mutex_unlock(philo->rm);
			}
		}
	}
	return (*error || philo->ate >= philo->conf->notepme);
}

int	phsleep(t_philo *philo, size_t t, int *error, t_state *state)
{
	if (!log_state(philo->conf->stt, philo->id, LOG_SLEEP, error))
	{
		if (t + philo->conf->te + philo->conf->ts < philo->ttd)
			usleep(philo->conf->ts);
		else
			die(philo, error, state);
	}
	return (*error);
}

int	think(t_philo *philo, size_t t, int *error, t_state *state)
{
	if (!log_state(philo->conf->stt, philo->id, LOG_THINK, error))
	{
		if (t < philo->ttd)
			safe_sleep(t);
		else
			die(philo, error, state);
	}
	return (*error);
}

static int	die(t_philo *philo, int *error, t_state *state)
{
	safe_sleep(philo->ttd);
	if (!mut_lock(&state->sm, PHILOSOPHER_ERR_MUT_DL, error))
	{
		if (!(state->state || log_state(philo->conf->stt, philo->id, LOG_DIE,
					error)))
		{
			*error = PHILOSOPHER_DIED;
			state->state = PHILOSOPHER_DIED;
		}
		pthread_mutex_unlock(&state->sm);
	}
	return (*error);
}
