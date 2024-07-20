/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remap.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 06:14:45 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/19 02:52:12 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMAP_H
# define REMAP_H
# include <pthread.h>

int	mut_init(pthread_mutex_t *m, int code, int *error);
int	mut_lock(pthread_mutex_t *m, int code, int *error);
int	mut_dest(pthread_mutex_t *m, int code, int *error);
int	thr_join(pthread_t t, int *error);
int	thr_crea(pthread_t *t, void *(*func)(void *), void *arg, int *error);

#endif
