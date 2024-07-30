/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 07:53:41 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/26 07:46:45 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H
# define TIME_GAP_US 100UL

typedef struct s_conf
{
	unsigned int	td;
	unsigned int	te;
	unsigned int	ts;
	unsigned long	nop;
	unsigned long	notepme;
	unsigned long	stt;
	int				ewf;
}	t_conf;

typedef union u_config
{
	t_conf	conf;
	struct	s_conf_arr
	{
		unsigned int	iarr[3];
		unsigned long	larr[3];
		int				swd;
	}	conf_arr;
}	t_config;
#endif
