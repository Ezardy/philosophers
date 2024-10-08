/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:47:36 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/02 06:16:59 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include "stddef.h"

void	print_error(int error);
int		log_state(size_t start_time, size_t i, int code, int *error);
int		init_logger(int *error);
void	destroy_logger(int global);

#endif
