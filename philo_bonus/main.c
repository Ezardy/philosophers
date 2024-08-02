/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 01:04:30 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/02 06:36:30 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "logger/error_codes.h"
#include "logger/logger.h"
#include "parser/parser.h"
#include "philosopher/philosopher.h"

static void	ms_to_us(t_conf *conf);

int	main(const int argc, const char **argv)
{
	int				i;
	int				error;
	t_config		conf;

	error = (argc < 5 || argc > 6) * MAIN_ERR_ARG_COUNT;
	if (!error)
	{
		i = 1;
		conf.conf.ewf = argc == 6;
		while (!error && i++ < 4)
			error = read_uint_limit(argv[i], conf.conf_arr.iarr + (i - 2),
					UINT_MAX / 1000);
		while (!error && i++ < 6 + (argc == 6))
			error = read_ulong(argv[(i - 6) * 4 + 1],
					conf.conf_arr.larr + (i - 6));
	}
	if (!init_logger(&error))
	{
		ms_to_us(&conf.conf);
		if (conf.conf.nop)
			error = awake_philosophers(&conf.conf);
		destroy_logger(1);
	}
	print_error(error);
	return (error);
}

static void	ms_to_us(t_conf *conf)
{
	conf->td *= 1000;
	conf->te *= 1000;
	conf->ts *= 1000;
}
