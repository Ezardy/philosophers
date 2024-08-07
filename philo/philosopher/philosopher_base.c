/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:23:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/07 18:06:36 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#include "logger/error_codes.h"
#include "remap/remap.h"
#include "t_philo.h"
#include "t_state.h"

int			eat(t_philo *philo, int *error, t_state *state);
int			phsleep(t_philo *philo, int *error, t_state *state);
int			think(t_philo *philo, int *error, t_state *state);

static void	step(t_philo *philo);
static void	logic_odd(t_philo *philo, int *error, t_state *state);
static void	logic_even(t_philo *philo, int *error, t_state *state);
static void	set_error(int *err, t_state *state);

void	*philosopher_base(t_philo *philo, int mode)
{
	static t_state	state = {0};

	err = 0;
	if (mode == 1)
		mut_init(&state.sm, PHILOSOPHER_ERR_MEM_ALLOC, &err);
	else if (mode == 2)
		mut_dest(&state.sm, PHILOSOPHER_ERR_MUT_BUSY, &err);
	else
	{
		safe_sleep(philo->te[0]);
		while ((!philo->conf->ewf || philo->ate < philo->conf->notepme) && !philo->error)
			logic(philo, &err, &state);
	}
	return ((void *)(long)err);
}

static void	logic_odd(t_philo *philo, int *err, t_state *state)
{
	if ((philo->i == philo->conf->nop - 1) && (philo->i % 2 == 0))
	{
		philo->i = (philo->i + 1) % philo->conf->nop;
		if (philo->tec == philo->te)
			philo->tec = philo->te + 1;
		else
		{
			step(philo);
			philo->tec = philo->te;
		}
	}
	think(philo, err, state);
	eat(philo, err, state);
	phsleep(philo, err, state);
	step(philo);
	philo->i = (philo->i + 2) % philo->conf->nop;
	set_error(err, state);
}

static void	logic_even(t_philo *philo, int *err, t_state *state)
{
	eat(philo, err, state);
	phsleep(philo, err, state);
	step(philo);
	philo->i = (philo->i + 1) % philo->conf->nop;
	if ((philo->i == philo->conf->nop - 1) && (philo->i % 2 == 0))
	{
		philo->i = (philo->i + 1) % philo->conf->nop;
		if (philo->tec == philo->te)
			philo->tec = philo->te + 1;
		else
		{
			step(philo);
			philo->tec = philo->te;
		}
	}
	think(philo, err, state);
	philo->i = (philo->i + 1) % philo->conf->nop;
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

	if (philo->te[1] - philo->te[0] + philo->conf->te > philo->conf->ts)
		rem = philo->te[1] + philo->conf->te - philo->te[0] - philo->conf->ts;
	else
		rem = 0;
	philo->te[0] = philo->te[0] + philo->conf->ts + rem;
	philo->te[1] = philo->te[0] + philo->conf->te;
}
