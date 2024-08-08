/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:20:55 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/08 00:51:06 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/_types/_size_t.h>
#include <sys/time.h>
#include <unistd.h>

#include "logger/state_codes.h"
#include "logger/error_codes.h"
#include "logger/logger.h"
#include "remap/remap.h"
#include "t_philo.h"
#include "t_state.h"

static int	die(t_philo *philo, t_state *state);
static void	update_stats(t_philo *philo);

int	eat(t_philo *philo, t_state *state)
{
	if (!(mut_lock(philo->lm, PHILOSOPHER_ERR_MUT_DL, &philo->error)
			|| log_state(philo, LOG_TAKE_FORK)))
	{
		if (philo->lm == philo->rm)
		{
			die(philo, state);
			pthread_mutex_unlock(philo->lm);
		}
		else
		{
			if (!(mut_lock(philo->rm, PHILOSOPHER_ERR_MUT_DL, &philo->error)
					|| log_state(philo, LOG_TAKE_FORK)
					|| log_state(philo, LOG_EAT)))
			{
				update_stats(philo);
				if (philo->ttd > *philo->tec + philo->conf->te)
					usleep(philo->conf->te);
				else
					die(philo, state);
				pthread_mutex_unlock(philo->lm);
				pthread_mutex_unlock(philo->rm);
			}
		}
	}
	return (philo->error || philo->ate >= philo->conf->notepme);
}

static void	update_stats(t_philo *philo)
{
	size_t	cur_time;

	cur_time = gettime();
	philo->ttd = cur_time + philo->conf->td;
	philo->ate += 1;
	philo->te[1] += cur_time - *philo->tec;
	philo->te[0] += cur_time - *philo->tec;
}

int	phsleep(t_philo *philo, size_t t, t_state *state)
{
	if (!log_state(philo, LOG_SLEEP))
	{
		if (t + philo->conf->te + philo->conf->ts < philo->ttd)
			usleep(philo->conf->ts);
		else
			die(philo, state);
	}
	return (philo->error);
}

int	think(t_philo *philo, t_state *state)
{
	if (!log_state(philo, LOG_THINK))
	{
		if (*philo->tec < philo->ttd)
			safe_sleep(*philo->tec);
		else
			die(philo, state);
	}
	return (philo->error);
}

static int	die(t_philo *philo, t_state *state)
{
	safe_sleep(philo->ttd);
	if (!mut_lock(&state->sm, PHILOSOPHER_ERR_MUT_DL, &philo->error))
	{
		if (!(state->state || log_state(philo, LOG_DIE)))
		{
			philo->error = PHILOSOPHER_DIED;
			state->state = PHILOSOPHER_DIED;
		}
		pthread_mutex_unlock(&state->sm);
	}
	return (philo->error);
}
