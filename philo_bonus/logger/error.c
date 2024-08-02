/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:51:02 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/01 01:23:01 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "error_codes.h"

void	print_main_error(int error);
void	print_parser_error(int error);
void	print_philosopher_error(int error);
void	print_pid_list_error(int error);
void	print_logger_error(int error);

void	print_error(int error)
{
	if (error && error < PHILOSOPHER_DIED)
	{
		printf("error: ");
		if (error >= MAIN_ERR_BEGIN && error <= MAIN_ERR_END)
			print_main_error(error);
		else if (error >= PARSER_ERR_BEGIN && error <= PARSER_ERR_END)
			print_parser_error(error);
		else if (error >= PHILOSOPHER_ERR_BEGIN && error <= PHILOSOPHER_ERR_END)
			print_philosopher_error(error);
		else if (error >= LOGGER_ERR_BEGIN && error <= LOGGER_ERR_END)
			print_logger_error(error);
		else
			print_pid_list_error(error);
	}
}
