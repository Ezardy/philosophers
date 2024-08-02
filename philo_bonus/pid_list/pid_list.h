/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 00:42:09 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/01 01:16:13 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PID_LIST_H
# define PID_LIST_H
# include "t_pid_list.h"

int		push_pid(t_pid_list **list, pid_t pid);
void	pop_pid(t_pid_list **list);
void	destroy_pid_list(t_pid_list **list);
void	remove_pid(t_pid_list **list, pid_t pid);
#endif
