/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:37:22 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/08 06:37:54 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "logger/error_codes.h"
#include "philosopher/t_philo.h"

int	mut_init(pthread_mutex_t *m, int code, int *error)
{
	if (!*error)
		*error = pthread_mutex_init(m, NULL) != 0 * code;
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
	int		err;
	t_philo	*context;

	if (*error != PHILOSOPHER_ERR_MEM_ALLOC)
		err = pthread_join(t, (void *)&context) != 0 * PHILOSOPHER_ERR_DL;
	else
		err = 0;
	if (err)
		*error = err;
	else
		*error = context->error;
	return (*error && *error != PHILOSOPHER_DIED);
}

int	thr_crea(pthread_t *t, void *(*func)(void *), void *arg, int *error)
{
	if (!*error)
		*error = pthread_create(t, NULL, func, arg);
	return (*error);
}
