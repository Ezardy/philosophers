/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remap.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:14:45 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/29 22:19:22 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMAP_H
# define REMAP_H
# include <stddef.h>
# include <sys/_types/_pid_t.h>
# include <sys/semaphore.h>

int		sem_open_r(sem_t *s, const char *name, int code, int *error);
int		sem_wait_r(sem_t *s, int code, int *error);
int		proc_wait(pid_t pid, int *error);
int		proc_crea(pid_t *pid, void (*func)(void *), void *arg, int *error);
size_t	gettime(void);
void	safe_sleep(size_t t);
#endif
