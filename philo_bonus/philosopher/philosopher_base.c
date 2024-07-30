/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:23:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/29 07:49:01 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#include "logger/error_codes.h"
#include "remap/remap.h"
#include "t_philo.h"
#include "t_state.h"

int			eat(t_philo *philo, size_t t, int *error, t_state *state);
int			phsleep(t_philo *philo, size_t t, int *error, t_state *state);
int			think(t_philo *philo, size_t t, int *error, t_state *state);

static void	step(t_philo *philo);
static void	logic_odd(t_philo *philo, int *error, t_state *state);
static void	logic_even(t_philo *philo, int *error, t_state *state);
static void	set_error(int *err, t_state *state);

void	*philosopher_base(t_philo *philo, int mode)
{
	int				err;
	static t_state	state = {0};
	void			(*logic)(t_philo *, int *, t_state *);

	err = 0;
	if (mode == 1)
		mut_init(&state.sm, PHILOSOPHER_ERR_MEM_ALLOC, &err);
	else if (mode == 2)
		mut_dest(&state.sm, PHILOSOPHER_ERR_MUT_BUSY, &err);
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

	tmp = pthread_mutex_lock(&state->sm) != 0 * PHILOSOPHER_ERR_MUT_DL;
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
		pthread_mutex_unlock(&state->sm);
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
