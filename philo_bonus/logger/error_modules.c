/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_modules.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 01:18:41 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/01 01:21:28 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "error_codes.h"

void	print_logger_error(int error)
{
	const char	*str;

	if (error == LOGGER_ERR_SEM_NOSPC)
		str = LOGGER_ERR_SEM_NOSPC_DESK;
	else if (error == LOGGER_ERR_SEM_ENFILE)
		str = LOGGER_ERR_SEM_ENFILE_DESK;
	else if (error == LOGGER_ERR_SEM_EMFILE)
		str = LOGGER_ERR_SEM_EMFILE_DESK;
	else
		str = LOGGER_ERR_SEM_DL_DESK;
	printf("logger: %s\n", str);
}

void	print_philosopher_error(int error)
{
	const char	*str;

	if (error == PHILOSOPHER_ERR_PROC_MEM)
		str = PHILOSOPHER_ERR_PROC_MEM_DESK;
	else if (error == PHILOSOPHER_ERR_SEM_DL)
		str = PHILOSOPHER_ERR_SEM_DL_DESK;
	else if (error == PHILOSOPHER_ERR_PROC_LIM)
		str = PHILOSOPHER_ERR_PROC_LIM_DESK;
	else if (error == PHILOSOPHER_ERR_SEM_NOSPC)
		str = PHILOSOPHER_ERR_SEM_NOSPC_DESK;
	else if (error == PHILOSOPHER_ERR_SEM_ENFILE)
		str = PHILOSOPHER_ERR_SEM_ENFILE_DESK;
	else
		str = PHILOSOPHER_ERR_SEM_EMFILE_DESK;
	printf("philosopher: %s\n", str);
}

void	print_parser_error(int error)
{
	const char	*str;

	if (error == PARSER_ERR_NEG_VAL)
		str = PARSER_ERR_NEG_VAL_DESC;
	else if (error == PARSER_ERR_EMP_STR)
		str = PARSER_ERR_EMP_STR_DESC;
	else if (error == PARSER_ERR_NON_DIG)
		str = PARSER_ERR_NON_DIG_DESC;
	else
		str = PARSER_ERR_NUM_BIG_DESC;
	printf("parser: %s\n%s", str, HELP_MSG);
}

void	print_main_error(int error)
{
	const char	*str;

	(void)error;
	str = MAIN_ERR_ARG_COUNT_DESC;
	printf("main: %s\n%s", str, HELP_MSG);
}

void	print_pid_list_error(int error)
{
	const char	*str;

	(void)error;
	str = PID_LIST_ERR_MEMALLOC_DESK;
	printf("pid_list: %s\n", str);
}
