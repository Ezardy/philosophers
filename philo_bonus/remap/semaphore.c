/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:37:22 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/02 07:03:46 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/_types/_pid_t.h>
#include <sys/semaphore.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#include "logger/error_codes.h"
#include "t_sem_init.h"

int	sem_open_r(sem_t *s, const t_sem_init *si, int code, int *error)
{
	int err;
	if (!*error)
	{
		s = sem_open(si->name, O_CREAT | O_EXCL, S_IRUSR + S_IWUSR, si->n);
		err = errno;
		if (s == SEM_FAILED)
		{
			if (err == EMFILE)
				*error = (code == PHILOSOPHER_ERR_BEGIN)
					* PHILOSOPHER_ERR_SEM_EMFILE + (code == LOGGER_ERR_BEGIN)
					* LOGGER_ERR_SEM_EMFILE;
			else if (err == ENFILE)
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

int	sem_wait_r(sem_t *s, int code, int *error)
{
	if (!*error)
	{
		*error = sem_wait(s);
		if (*error == -1)
			*error = (code == PHILOSOPHER_ERR_BEGIN) * PHILOSOPHER_ERR_SEM_DL
				+ (code == LOGGER_ERR_BEGIN) * LOGGER_ERR_SEM_DL;
	}
	return (*error);
}
