/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 01:37:47 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/28 23:09:59 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "remap/remap.h"
#include "logger/error_codes.h"
#include "config.h"
#include "t_philo.h"

int			dest_philosopher_func(int *error);
int			init_philosopher_func(int *error);
void		*philosopher(void *philo);

static int	run_threads(pthread_t *phs, pthread_mutex_t *fms, t_conf *conf);
static int	run_threads_loop(t_philosophers *philos, pthread_t *phs);

int	awake_philosophers(t_conf *conf)
{
	int				error;
	pthread_t		*phs;
	pthread_mutex_t	*fms;

	phs = (pthread_t *)malloc(sizeof(pthread_t) * conf->nop);
	fms = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * conf->nop);
	error = (phs == NULL || fms == NULL)
		* PHILOSOPHER_ERR_MEM_ALLOC;
	if (!init_philosopher_func(&error))
	{
		error = run_threads(phs, fms, conf);
		dest_philosopher_func(&error);
	}
	free(fms);
	free(phs);
	return (error);
}

static int	run_threads(pthread_t *phs, pthread_mutex_t *fms, t_conf *conf)
{
	int				err;
	size_t			i;
	t_philosophers	philos;

	philos.philos = (t_philo *)malloc(sizeof(t_philo) * conf->nop);
	philos.conf = conf;
	philos.fms = fms;
	err = (philos.philos == NULL) * PHILOSOPHER_ERR_MEM_ALLOC;
	i = 0;
	while (i < conf->nop && !mut_init(fms + i, PHILOSOPHER_ERR_MEM_ALLOC, &err))
		i = i + 1;
	if (!err)
		err = run_threads_loop(&philos, phs);
	i = 0;
	while (i < philos.conf->nop && !thr_join(phs[i], &err))
		i = i + 1;
	free(philos.philos);
	i = 0;
	while (i < conf->nop && !mut_dest(fms + i, PHILOSOPHER_ERR_MUT_BUSY, &err))
		i = i + 1;
	return (err);
}

static int	run_threads_loop(t_philosophers *philos, pthread_t *phs)
{
	int					error;
	size_t				i;
	const unsigned long	delay = 500000;

	i = 0;
	error = 0;
	philos->conf->stt = gettime() + delay;
	while (!error && i < philos->conf->nop)
	{
		philos->philos[i].teo = philos->conf->stt;
		philos->philos[i].tee = philos->conf->stt + philos->conf->te;
		philos->philos[i].ttd = philos->conf->stt + philos->conf->td;
		philos->philos[i].conf = philos->conf;
		philos->philos[i].id = i + 1;
		philos->philos[i].i = i;
		philos->philos[i].lm = philos->fms + (i + 1) % philos->conf->nop;
		philos->philos[i].rm = philos->fms + i;
		philos->philos[i].ate = 0;
		thr_crea(phs + i, philosopher, philos->philos + i, &error);
		i += 1;
	}
	return (error);
}
