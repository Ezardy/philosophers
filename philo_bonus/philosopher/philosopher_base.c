/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:23:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/04 04:01:13 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/semaphore.h>
#include <unistd.h>
#include <sys/time.h>

#include "logger/error_codes.h"
#include "remap/remap.h"
#include "t_philo.h"
#include "remap/t_sem_init.h"

int			eat(t_philo *philo, size_t t, int *error, sem_t *ds);
int			phsleep(t_philo *philo, size_t t, int *error, sem_t *ds);
int			think(t_philo *philo, size_t t, int *error, sem_t *ds);

static void	step(t_philo *philo);
static void	logic_odd(t_philo *philo, int *error, sem_t *ds);
static void	logic_even(t_philo *philo, int *error, sem_t *ds);
static void	set_error(int *err, sem_t *ds);

int	philosopher_base(t_philo *philo, int mode)
{
	int					err;
	static sem_t		*ds;
	const t_sem_init	sem_init = {"philosophers_global_state", 1};
	void				(*logic)(t_philo *, int *, sem_t *);

	err = 0;
	if (mode == 1)
		sem_open_r(&ds, &sem_init, PHILOSOPHER_ERR_BEGIN, &err);
	else if (mode == 2)
	{
		sem_close(ds);
		sem_unlink(sem_init.name);
	}
	else
	{
		if (philo->id % 2)
			logic = logic_odd;
		else
			logic = logic_even;
		safe_sleep(philo->teo);
		while ((!philo->conf->ewf || philo->ate < philo->conf->notepme) && !err)
			logic(philo, &err, ds);
		sem_close(ds);
	}
	return (err);
}

static void	logic_odd(t_philo *philo, int *err, sem_t *ds)
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
	think(philo, te, err, ds);
	eat(philo, te, err, ds);
	phsleep(philo, te, err, ds);
	step(philo);
	set_error(err, ds);
}

static void	logic_even(t_philo *philo, int *err, sem_t *ds)
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
	eat(philo, te, err, ds);
	phsleep(philo, te, err, ds);
	think(philo, te, err, ds);
	step(philo);
	set_error(err, ds);
}

static void	set_error(int *err, sem_t *ds)
{
	if (!(sem_wait_r(ds, PHILOSOPHER_ERR_BEGIN, err) || *err))
		sem_post(ds);
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
