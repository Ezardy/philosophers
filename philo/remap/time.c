/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:50:17 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/22 23:51:08 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>

size_t	gettime(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000000 + tp.tv_usec);
}

void	safe_sleep(size_t t)
{
	size_t	cur;

	cur = gettime();
	if (t > cur)
		usleep((useconds_t)(t - cur));
}
