/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:23:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/31 15:32:48 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/semaphore.h>
#include <unistd.h>
#include <sys/time.h>

#include "logger/error_codes.h"
#include "remap/remap.h"
#include "t_philo.h"
#include "t_state.h"
#include "remap/t_sem_init.h"

int			eat(t_philo *philo, size_t t, int *error, t_state *state);
int			phsleep(t_philo *philo, size_t t, int *error, t_state *state);
int			think(t_philo *philo, size_t t, int *error, t_state *state);

static void	step(t_philo *philo);
static void	logic_odd(t_philo *philo, int *error, t_state *state);
static void	logic_even(t_philo *philo, int *error, t_state *state);
static void	set_error(int *err, t_state *state);

void	*philosopher_base(t_philo *philo, int mode)
{
	int					err;
	static t_state		state = {0};
	const t_sem_init	sem_init = {"philosophers_global_state", 1};
	void				(*logic)(t_philo *, int *, t_state *);

	err = 0;
	if (mode == 1)
		sem_open_r(state.ss, &sem_init, PHILOSOPHER_ERR_BEGIN, &err);
	else if (mode == 2)
		sem_close(state.ss);
	else
	{
		if (philo->id % 2)
			logic = logic_odd;
		else
			logic = logic_even;
		safe_sleep(philo->teo);
		while ((!philo->conf->ewf || philo->ate < philo->conf->notepme) && !err)
			logic(philo, &err, &state);
	}
	return ((void *)(long)err);
}

static void	logic_odd(t_philo *philo, int *err, t_state *state)
{
	size_t	te;

	if ((philo->i == philo->conf->nop - 1) && (philo->i % 2 == 0))
	{
		step(philo);
		te = philo->teo;
	}
	else if (philo->i % 2)
		te = philo->teo;
	else
		te = philo->tee;
	think(philo, te, err, state);
	eat(philo, te, err, state);
	phsleep(philo, te, err, state);
	step(philo);
	set_error(err, state);
}

static void	logic_even(t_philo *philo, int *err, t_state *state)
{
	size_t	te;

	if ((philo->i == philo->conf->nop - 1) && (philo->i % 2 == 0))
	{
		step(philo);
		te = philo->teo;
	}
	else if (philo->i % 2)
		te = philo->teo;
	else
		te = philo->tee;
	eat(philo, te, err, state);
	phsleep(philo, te, err, state);
	think(philo, te, err, state);
	step(philo);
	set_error(err, state);
}

static void	set_error(int *err, t_state *state)
{
	int	tmp;

	tmp = sem_wait_r(state->ss, PHILOSOPHER_ERR_BEGIN, err);
	if (state->state)
		*err = state->state;
	else
	{
		if (tmp)
			state->state = tmp;
		else if (*err)
			state->state = *err;
	}
	if (!tmp)
		sem_post(state->ss);
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
