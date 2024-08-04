/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:11:30 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/04 04:03:54 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/semaphore.h>
#include <sys/time.h>

#include "logger/error_codes.h"
#include "remap/t_sem_init.h"
#include "state_codes.h"
#include "remap/remap.h"

static int			log_state_base(size_t start_time, size_t i, int code,
						int mode);
static const char	*sel_desk(int code);

int	log_state(size_t start_time, size_t i, int code, int *error)
{
	if (!*error)
		*error = log_state_base(start_time, i, code, 0);
	return (*error);
}

int	init_logger(int *error)
{
	if (!*error)
		*error = log_state_base(0, 0, 0, 1);
	return (*error);
}

void	destroy_logger(int global)
{
	log_state_base(0, 0, 0, 2 + global);
}

static int	log_state_base(size_t start_time, size_t i, int code, int mode)
{
	int						error;
	static sem_t			*s;
	const t_sem_init		sem_init = {"philo_logger", 1};

	error = 0;
	if (mode == 1)
		sem_open_r(&s, &sem_init, code, &error);
	else if (mode == 2)
		sem_close(s);
	else if (mode == 3)
	{
		sem_close(s);
		sem_unlink(sem_init.name);
	}
	else
	{
		if (!sem_wait_r(s, LOGGER_ERR_BEGIN, &error))
		{
			printf("%li %li %s\n", (gettime() - start_time) / 1000, i,
				sel_desk(code));
			sem_post(s);
		}
	}
	return (error);
}

static const char	*sel_desk(int code)
{
	const char				*desk;

	if (code == LOG_TAKE_FORK)
		desk = LOG_TAKE_FORK_DESK;
	else if (code == LOG_EAT)
		desk = LOG_EAT_DESK;
	else if (code == LOG_SLEEP)
		desk = LOG_SLEEP_DESK;
	else if (code == LOG_THINK)
		desk = LOG_THINK_DESK;
	else
		desk = LOG_DIE_DESK;
	return (desk);
}
