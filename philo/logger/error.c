/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:51:02 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/25 07:31:34 by zanikin          ###   ########.fr       */
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
		if (error >= MAIN_ERR_ARG_COUNT && error < PARSER_ERR_NEG_VAL)
			print_main_error(error);
		else if (error >= PARSER_ERR_NEG_VAL
			&& error < PHILOSOPHER_ERR_MEM_ALLOC)
			print_parser_error(error);
		else if (error >= PHILOSOPHER_ERR_MEM_ALLOC && error
			< LOGGER_ERR_MUT_DEAD_LOCK)
			print_philosopher_error(error);
		else
			print_logger_error(error);
	}
}

static void	print_logger_error(int error)
{
	const char	*str;

	if (error == LOGGER_ERR_MUT_DEAD_LOCK)
		str = LOGGER_ERR_MUT_DEAD_LOCK_DESK;
	else if (error == LOGGER_ERR_MUT_BUSY)
		str = LOGGER_ERR_MUT_BUSY_DESK;
	else
		str = LOGGER_ERR_MEM_ALLOC_DESK;
	printf("logger: %s\n", str);
}

static void	print_philosopher_error(int error)
{
	const char	*str;

	if (error == PHILOSOPHER_ERR_MEM_ALLOC)
		str = PHILOSOPHER_ERR_MEM_ALLOC_DESK;
	else if (error == PHILOSOPHER_ERR_DL)
		str = PHILOSOPHER_ERR_DL_DESK;
	else if (error == PHILOSOPHER_ERR_MUT_DL)
		str = PHILOSOPHER_ERR_MUT_DL_DESK;
	else
		str = PHILOSOPHER_ERR_MUT_BUSY_DESK;
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
