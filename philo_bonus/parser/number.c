/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:22:20 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/23 22:19:30 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger/error_codes.h"

int					read_ulong(const char *str, unsigned long *out);

static int			iszero(char c);
static int			isspace(char c);
static const char	*skip_symbol(const char *str, int (*f)(char c));

int	read_uint_limit(const char *str, unsigned int *out, unsigned int limit)
{
	int				error;
	unsigned long	res;

	error = read_ulong(str, &res);
	if (!error)
		error = (res > limit) * PARSER_ERR_NUM_BIG;
	if (!error)
		*out = (unsigned int)res;
	return (error);
}

int	read_ulong(const char *str, unsigned long *out)
{
	int	error;
	int	d_count;

	*out = 0;
	str = skip_symbol(str, isspace);
	error = (*str == '-') * PARSER_ERR_NEG_VAL + (!*str) * PARSER_ERR_EMP_STR;
	if (!error)
	{
		str = skip_symbol(str, iszero);
		d_count = 0;
		while (d_count < 19 && !(*str < '0' || *str > '9'))
		{
			*out = *out * 10 + str++[0] - '0';
			d_count++;
		}
		error = (*str && (d_count < 19 || *str < '0' || *str > '9'))
			* PARSER_ERR_NON_DIG + (d_count == 19 && *str >= '0' && *str <= '9'
				&& (str[1] || *out > 1844674407370955161
					|| (*out == 1844674407370955161 && *str > '5')))
			* PARSER_ERR_NUM_BIG;
		if (!error && d_count == 19 && *str)
			*out = *out * 10 + *str - '0';
	}
	return (error);
}

static const char	*skip_symbol(const char *str, int (*f)(char c))
{
	while (f(*str))
		str += 1;
	return (str);
}

static int	isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	iszero(char c)
{
	return (c == '0');
}
