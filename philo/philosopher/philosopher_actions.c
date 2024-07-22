/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:20:55 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/22 01:08:02 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

#include "logger/state_codes.h"
#include "logger/error_codes.h"
#include "logger/logger.h"
#include "t_philo.h"
#include "remap/remap.h"

int	eat(t_philo *philo, int *error)
{
	if (!(mut_lock(philo->lm, PHILOSOPHER_ERR_MUT_DL, error)
			|| log_state(philo->i, LOG_TAKE_FORK, error)
			|| mut_lock(philo->rm, PHILOSOPHER_ERR_MUT_DL, error)
			|| log_state(philo->i, LOG_TAKE_FORK, error)
			|| log_state(philo->i, LOG_EAT, error)))
	{
		usleep((useconds_t)(philo->conf->te * 1000));
		philo->ate += 1;
		pthread_mutex_unlock(philo->lm);
		pthread_mutex_unlock(philo->rm);
	}
	return (*error || philo->ate >= philo->conf->notepme);
}

int	phsleep(useconds_t ts, size_t i, int *error)
{
	if (!log_state(i, LOG_SLEEP, error))
		usleep((useconds_t)(ts * 1000));
	return (*error);
}

int	think(t_philo *philo, suseconds_t t, int *error)
{
	suseconds_t		rem;
	struct timeval	tp;

	if (!log_state(philo->i, LOG_THINK, error))
	{
		gettimeofday(&tp, NULL);
		rem = t - tp.tv_usec;
		if (rem > 0)
			usleep(rem);
		rem = philo->tee + philo->conf->te - philo->teo - philo->conf->ts;
		philo->teo = philo->teo + philo->conf->ts + (rem > 0) * rem;
		philo->tee = philo->teo + philo->conf->te;
	}
	return (*error);
}
