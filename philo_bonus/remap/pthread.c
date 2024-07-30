/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:37:22 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/29 23:25:02 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/semaphore.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>

#include "logger/error_codes.h"
#include "t_sem_init.h"

int		sem_open_r(sem_t *s, t_sem_init *si, int code, int *error)
{
	if (!*error)
		s = sem_open(si->name, O_CREAT | O_EXCL, S_IRUSR + S_IWUSR, si->nop);
	return (*error);
}

int	mut_lock(pthread_mutex_t *m, int code, int *error)
{
	if (!*error)
		*error = pthread_mutex_lock(m) != 0 * code;
	return (*error);
}

int	mut_dest(pthread_mutex_t *m, int code, int *error)
{
	if (!*error)
		*error = pthread_mutex_destroy(m) != 0 * code;
	return (*error);
}

int	thr_join(pthread_t t, int *error)
{
	int	err;

	if (!*error)
		err = pthread_join(t, (void *)error) != 0 * PHILOSOPHER_ERR_DL;
	else
		err = 0;
	if (err)
		*error = err;
	return (*error);
}

int	thr_crea(pthread_t *t, void *(*func)(void *), void *arg, int *error)
{
	if (!*error)
		*error = pthread_create(t, NULL, func, arg);
	return (*error);
}
