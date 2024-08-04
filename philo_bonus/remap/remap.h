/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remap.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:14:45 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/04 04:01:39 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMAP_H
# define REMAP_H
# include <stddef.h>
# include <sys/_types/_pid_t.h>
# include <sys/semaphore.h>

# include "t_sem_init.h"

int		sem_open_r(sem_t **s, const t_sem_init *si, int code, int *error);
int		sem_wait_r(sem_t *s, int code, int *error);
int		proc_wait(pid_t pid, int *error);
size_t	gettime(void);
void	safe_sleep(size_t t);
#endif
