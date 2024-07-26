/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:23:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/26 07:37:48 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#include "t_philo.h"
#include "logger/error_codes.h"
#include "remap/remap.h"

int			eat(t_philo *philo, size_t t, int *error);
int			phsleep(t_philo *philo, size_t t, int *error);
int			think(t_philo *philo, size_t t, int *error);

static void	step(t_philo *philo);
static void	logic(t_philo *philo, int *error, int *g_state,
				pthread_mutex_t *sm);
static void	set_error(pthread_mutex_t *sm, int *err, int *g_state);

void	*philosopher_base(t_philo *philo, int mode)
{
	int						err;
	static int				g_state;
	static pthread_mutex_t	sm;

	err = 0;
	if (mode == 1)
	{
		g_state = 0;
		mut_init(&sm, PHILOSOPHER_ERR_MEM_ALLOC, &err);
	}
	else if (mode == 2)
		mut_dest(&sm, PHILOSOPHER_ERR_MUT_BUSY, &err);
	else
	{
		safe_sleep(philo->teo);
		while ((!philo->conf->ewf || philo->ate < philo->conf->notepme) && !err)
			logic(philo, &err, &g_state, &sm);
	}
	return ((void *)(long)err);
}

static void	logic(t_philo *philo, int *err, int *g_state, pthread_mutex_t *sm)
{
	size_t	te;

	if (philo->i < philo->conf->nop - 1 || philo->i % 2)
	{
		if (philo->i % 2 == 0)
		{
			te = philo->tee;
			think(philo, te, err);
		}
		else
			te = philo->teo;
		eat(philo, te, err);
		phsleep(philo, te, err);
		if (philo->i % 2)
			think(philo, te, err);
		set_error(sm, err, g_state);
	}
	step(philo);
}

static void	set_error(pthread_mutex_t *sm, int *err, int *g_state)
{
	int	tmp;

	if (*err)
	{
		tmp = pthread_mutex_lock(sm) != 0 * PHILOSOPHER_ERR_MUT_DL;
		if (*g_state)
			*err = *g_state;
		else
			*g_state = tmp + !tmp * *err;
		if (!tmp)
			pthread_mutex_unlock(sm);
	}
}

static void	step(t_philo *philo)
{
	size_t	rem;

	if (philo->tee - philo->teo + philo->conf->te > philo->conf->ts)
		rem = philo->tee + philo->conf->te - philo->teo - philo->conf->ts;
	else
		rem = 0;
	philo->teo = philo->teo + philo->conf->ts + rem;
	philo->tee = philo->teo + philo->conf->te;
	philo->i = (philo->i + 1) % philo->conf->nop;
}
