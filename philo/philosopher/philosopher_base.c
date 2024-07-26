/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_base.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 05:23:53 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/26 00:54:16 by zanikin          ###   ########.fr       */
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
void		calc_eat_time(t_philo *philo);

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
		err = 0;
		safe_sleep(philo->teo);
		while ((!philo->conf->ewf || philo->ate < philo->conf->notepme) && !err)
			logic(philo, &err, &g_state, &sm);
	}
	return ((void *)(long)err);
}

static void	logic(t_philo *philo, int *err, int *g_state, pthread_mutex_t *sm)
{
	int		tmp;
	size_t	te;

	if (philo->i % philo->conf->nop == 0)
	{
		te = philo->tee;
		think(philo, te, err);
	}
	else
		te = philo->teo;
	eat(philo, te, err);
	phsleep(philo, te, err);
	if (philo->i % philo->conf->nop)
		think(philo, te, err);
	calc_eat_time(philo);
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
