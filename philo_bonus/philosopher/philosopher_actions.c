/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:20:55 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/08 07:20:52 by zanikin          ###   ########.fr       */
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
static void	update_stats(t_philo *philo);

int	eat(t_philo *philo, int *er, sem_t *ds)
{
	if (!(sem_wait_r(philo->s, PHILOSOPHER_ERR_BEGIN, er)
			|| log_state(philo->conf->stt, philo->id, LOG_TAKE_FORK, er)))
	{
		if (philo->conf->nop == 1)
		{
			die(philo, er, ds);
			sem_post(philo->s);
		}
		else
		{
			if (!(sem_wait_r(philo->s, PHILOSOPHER_ERR_BEGIN, er)
					|| log_state(philo->conf->stt, philo->id, LOG_TAKE_FORK, er)
					|| log_state(philo->conf->stt, philo->id, LOG_EAT, er)))
			{
				update_stats(philo);
				if (philo->ttd > *philo->tec + philo->conf->te)
					usleep(philo->conf->te);
				else
					die(philo, er, ds);
				sem_post(philo->s);
			}
		}
		sem_post(philo->s);
	}
	return (*er || philo->ate >= philo->conf->notepme);
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

int	phsleep(t_philo *philo, int *error, sem_t *ds)
{
	if (!log_state(philo->conf->stt, philo->id, LOG_SLEEP, error))
	{
		if (*philo->tec + philo->conf->ts < philo->ttd)
			usleep(philo->conf->ts);
		else
			die(philo, error, ds);
	}
	return (*error);
}

int	think(t_philo *philo, int *error, sem_t *ds)
{
	if (!log_state(philo->conf->stt, philo->id, LOG_THINK, error))
	{
		if (*philo->tec < philo->ttd)
			safe_sleep(*philo->tec);
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
