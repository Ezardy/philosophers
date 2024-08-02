/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_pid_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:48:01 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/01 00:41:54 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PID_LIST_H
# define T_PID_LIST_H
# include <sys/_types/_pid_t.h>

typedef struct s_pid_list
{
	struct s_pid_list	*n;
	pid_t				pid;
}	t_pid_list;
#endif
