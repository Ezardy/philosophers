/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:51:02 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/31 15:46:24 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "error_codes.h"

static void	print_main_error(int error);
static void	print_parser_error(int error);
static void	print_philosopher_error(int error);
static void	print_logger_error(int error);

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
		else
			print_logger_error(error);
	}
}

static void	print_logger_error(int error)
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

static void	print_philosopher_error(int error)
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

static void	print_parser_error(int error)
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

static void	print_main_error(int error)
{
	const char	*str;

	(void)error;
	str = MAIN_ERR_ARG_COUNT_DESC;
	printf("main: %s\n%s", str, HELP_MSG);
}
