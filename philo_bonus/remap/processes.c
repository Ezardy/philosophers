/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:37:22 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/30 19:06:30 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/_types/_pid_t.h>
#include <sys/semaphore.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <unistd.h>

#include "logger/error_codes.h"
#include "t_sem_init.h"

int	sem_open_r(sem_t *s, t_sem_init *si, int code, int *error)
{
	if (!*error)
	{
		s = sem_open(si->name, O_CREAT | O_EXCL, S_IRUSR + S_IWUSR, si->n);
		if (s == SEM_FAILED)
		{
			if (errno == EMFILE)
				*error = (code == PHILOSOPHER_ERR_BEGIN)
					* PHILOSOPHER_ERR_SEM_EMFILE + (code == LOGGER_ERR_BEGIN)
					* LOGGER_ERR_SEM_EMFILE;
			else if (errno == ENFILE)
				*error = (code == PHILOSOPHER_ERR_BEGIN)
					* PHILOSOPHER_ERR_SEM_ENFILE + (code == LOGGER_ERR_BEGIN)
					* LOGGER_ERR_SEM_ENFILE;
			else
				*error = (code == PHILOSOPHER_ERR_BEGIN)
					* PHILOSOPHER_ERR_SEM_NOSPC + (code == LOGGER_ERR_BEGIN)
					* LOGGER_ERR_SEM_NOSPC;
		}
	}
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

int	proc_crea(pid_t *pid, void (*func)(void *), void *arg, int *error)
{
	if (!*error)
	{
		*pid = fork();
		if (*pid == -1)
		{
			if (errno == EAGAIN)
				*error = PHILOSOPHER_ERR_PROC_LIM;
			else
				*error = PHILOSOPHER_ERR_PROC_MEM;
		}
	}
	return (*error);
}
