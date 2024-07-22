/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:11:30 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/22 01:52:49 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

#include "state_codes.h"
#include "error_codes.h"

static int			log_state_base(size_t i, int code, int mode);
static const char	*sel_desk(int code);

int	log_state(size_t i, int code, int *error)
{
	if (!*error)
		*error = log_state_base(i, code, 0);
	return (*error);
}

int	init_logger(int *error)
{
	if (!*error)
		*error = log_state_base(0, 0, 1);
	return (*error);
}

int	destroy_logger(int *error)
{
	if (!*error)
		*error = log_state_base(0, 0, 2);
	return (*error);
}

static int	log_state_base(size_t i, int code, int mode)
{
	int						error;
	struct timeval			tp;
	static pthread_mutex_t	m;

	if (mode == 1)
		error = pthread_mutex_init(&m, NULL) != 0 * LOGGER_ERR_MEM_ALLOC;
	else if (mode == 2)
		error = pthread_mutex_destroy(&m) != 0 * LOGGER_ERR_MUT_BUSY;
	else
	{
		gettimeofday(&tp, NULL);
		error = pthread_mutex_lock(&m) != 0 * LOGGER_ERR_MUT_DEAD_LOCK;
		if (!error)
		{
			printf("%i %li %s\n", tp.tv_usec, i, sel_desk(code));
			pthread_mutex_unlock(&m);
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
