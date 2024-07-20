/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 01:37:47 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/20 08:44:35 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "remap/remap.h"
#include "logger/error_codes.h"
#include "config.h"
#include "t_philo.h"

void		dest_philosopher_func(void);
int			init_philosopher_func(void);
void		*philosopher(t_philo *philo);

static int	run_threads(pthread_t *phs, pthread_mutex_t *fms,
				const t_conf *conf);
static int	run_threads_loop(const t_philosophers *philos, pthread_t *phs);
static void	set_philo(t_philosophers *philos, size_t i, size_t l, size_t r);

int	awake_philosophers(t_conf *conf)
{
	int				error;
	pthread_t		*phs;
	pthread_mutex_t	*fms;
	size_t			i;

	phs = (pthread_t *)malloc(sizeof(pthread_t) * conf->nop);
	fms = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * conf->nop);
	error = (phs == NULL || fms == NULL)
		* PHILOSOPHER_ERR_MEM_ALLOC;
	if (!error)
		error = run_threads(phs, fms, conf->nop);
	free(fms);
	free(phs);
	return (error);
}

static int	run_threads(pthread_t *phs, pthread_mutex_t *fms,
				const t_conf *conf)
{
	int				err;
	size_t			i;
	t_philosophers	philos;

	philos.sdied = 0;
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

static int	run_threads_loop(const t_philosophers *philos, pthread_t *phs)
{
	int				error;
	size_t			i;
	struct timeval	tp;

	i = 0;
	error = 0;
	gettimeofday(&tp, NULL);
	while (!error && i < philos->conf->nop)
	{
		philos->philos[i].teo = tp.tv_usec;
		philos->philos[i].tee = tp.tv_usec + philos->conf->te;
		if (i && i < philos->conf->nop - 1)
			set_philo(&philos, i, i - 1, i + 1);
		else if (!i)
			set_philo(&philos, 0, philos->conf->nop - 1, 0);
		else
			set_philo(&philos, philos->conf->nop - 1, philos->conf->nop - 1, 0);
		thr_crea(phs + i, philosopher, philos->philos + i, &error);
		i++;
	}
	return (error);
}

static void	set_philo(t_philosophers *philos, size_t i, size_t l, size_t r)
{
	philos->philos[i].conf = philos->conf;
	philos->philos[i].id = i + 1;
	philos->philos[i].i = i - 1;
	philos->philos[i].lm = philos->fms + l;
	philos->philos[i].rm = philos->fms + r;
	philos->philos[i].ate = 0;
}
