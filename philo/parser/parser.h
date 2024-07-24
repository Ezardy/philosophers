/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:18:37 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/23 22:19:50 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int	read_uint_limit(const char *str, unsigned int *out, unsigned int limit);
int	read_ulong(const char *str, unsigned long *out);
#endif
