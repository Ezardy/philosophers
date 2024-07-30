/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_state.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 04:24:49 by zanikin           #+#    #+#             */
/*   Updated: 2024/07/29 21:53:55 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_STATE_H
# define T_STATE_H
# include <sys/semaphore.h>

typedef struct s_state
{
	int				state;
	sem_t			*ss;
}	t_state;
#endif
