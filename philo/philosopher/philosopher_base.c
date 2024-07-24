/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:23:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/24 00:57:55 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#include "t_philo.h"
#include "logger/error_codes.h"
#include "remap/remap.h"

int			eat(t_philo *philo, size_t t, int *error);
int			phsleep(useconds_t ts, size_t i, int *error);
int			think(t_philo *philo, size_t t, int *error);

static void	*philosopher_base(t_philo *philo, int mode);
static void	logic(t_philo *philo, int *error, int *g_state,
				pthread_mutex_t *sm);

void	*philosopher(void *philo)
{
	return ((void *)philosopher_base((t_philo *)philo, 0));
}

int	init_philosopher_func(int *error)
{
	if (!*error)
		*error = (int)(long)philosopher_base(NULL, 1);
	return (*error);
}

int	dest_philosopher_func(int *error)
{
	if (!*error)
		*error = (int)(long)philosopher_base(NULL, 2);
	return (*error);
}

static void	*philosopher_base(t_philo *philo, int mode)
{
	int						err;
	static int				g_state;
	static pthread_mutex_t	sm;

	if (mode == 1)
	{
		g_state = 0;
		mut_init(&sm, PHILOSOPHER_ERR_MEM_ALLOC, &err);
	}
	else if (mode == 2)
		mut_dest(&sm, PHILOSOPHER_ERR_MUT_BUSY, &err);
	else
	{
		while ((!philo->conf->ewf || philo->ate < philo->conf->notepme) && !err)
		{
			if (!mut_lock(&sm, PHILOSOPHER_ERR_MUT_DL, &err))
				logic(philo, &err, &g_state, &sm);
			else
				g_state = err;
		}
		if (!err && philo->conf->ewf && philo->ate >= philo->conf->notepme)
			err = EAT_ENOUGH;
	}
	return ((void *)(long)err);
}

static void	logic(t_philo *philo, int *error, int *g_state, pthread_mutex_t *sm)
{
	int	st_m_err;

	if (!*g_state)
	{
		pthread_mutex_unlock(sm);
		if (philo->i % 2)
		{
			if (!(eat(philo, philo->teo, error) || phsleep(philo->conf->ts,
						philo->id, error)))
				think(philo, philo->teo, error);
		}
		else
			if (!(think(philo, philo->tee, error)
					|| eat(philo, philo->tee, error)))
				phsleep(philo->conf->ts, philo->id, error);
		philo->i = (philo->i + 1) % philo->conf->nop;
		if (*error)
		{
			st_m_err = pthread_mutex_lock(sm) != 0 * PHILOSOPHER_ERR_MUT_DL;
			if (!*g_state)
				*g_state = st_m_err + !st_m_err * *error;
			pthread_mutex_unlock(sm);
		}
	}
	else
		pthread_mutex_unlock(sm);
}
