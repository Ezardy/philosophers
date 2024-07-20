/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:53:41 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/10 06:20:18 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H
# define TIME_GAP_US 100UL

typedef struct s_conf
{
	unsigned long	nop;
	unsigned long	td;
	unsigned long	te;
	unsigned long	ts;
	unsigned long	notepme;
	int				swd;
}	t_conf;

typedef union u_config
{
	t_conf	conf;
	struct	s_conf_arr
	{
		unsigned long	arr[5];
		int				swd;
	}	conf_arr;
}	t_config;
#endif
