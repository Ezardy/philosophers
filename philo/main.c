/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:04:30 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/17 21:05:04 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging/error_codes.h"
#include "logging/error.h"
#include "parser/parser.h"
#include "philosopher/philosopher.h"

int	main(int argc, const char **argv)
{
	int			i;
	int			error;
	t_config	conf;

	error = (argc < 5 || argc > 6) * MAIN_ERR_ARG_COUNT;
	if (!error)
	{
		i = 1;
		conf.conf.swd = argc == 5;
		while (!error && i < argc)
			error = read_ulong(argv[i++], &conf.conf_arr.arr[i]);
	}
	if (!error && conf.conf.nop)
		error = awake_philosophers(&conf.conf);
	print_error(error);
	return (error);
}
