/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:22:20 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/05 02:20:36 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"
#include "parser_errors.h"

static int	isspace(char c);

int	read_ulong(const char *str, unsigned long *out)
{
	int	error;
	int	d_count;

	*out = 0;
	while (isspace(*str))
		str++;
	error = (*str == '-') * PARSER_ERR_NEG_VAL + (!*str) * PARSER_ERR_EMP_STR;
	if (!error)
	{
		d_count = 0;
		while (d_count < 19 && (*str < '0' || *str > '9'))
		{
			*out = *out * 10 + str++[0] - '0';
			d_count++;
		}
		error = (!*str && (d_count < 19 || *str < '0' || *str > '9'))
			* PARSER_ERR_NON_DIG + (d_count == 19 && (*str >= 0 || *str <= '9')
				&& (str[1] || *out > 1844674407370955161
					|| (*out == 1844674407370955161 && *str > '5')))
			* PARSER_ERR_NUM_BIG;
		if (!error && d_count == 19 && *str)
			*out = *out * 10 + *str - '0';
	}
	return (error | PARSER_INDEX);
}

static int	isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r');
}
