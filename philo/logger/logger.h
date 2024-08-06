/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:47:36 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/05 23:41:56 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include "stddef.h"

# include "philosopher/t_philo.h"

void	print_error(int error);
int		log_state(t_philo *philo, int code, int *error);
int		init_logger(int *error);
int		destroy_logger(int *error);

#endif
