/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:50:17 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/08 23:05:28 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>

void	usleep_r(useconds_t t, useconds_t offset);

size_t	gettime(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000000 + tp.tv_usec);
}

void	safe_sleep(size_t t, useconds_t offset)
{
	size_t	cur;

	cur = gettime();
	if (t > cur)
		usleep_r((useconds_t)(t - cur), offset);
}

void	usleep_r(useconds_t t, useconds_t offset)
{
	if (t > offset)
		usleep(t - offset);
}
