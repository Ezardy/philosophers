/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 18:46:36 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/09 18:25:26 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/_types/_pid_t.h>

#include "t_pid_list.h"
#include "logger/error_codes.h"

void	pop_pid(t_pid_list **list);

int	push_pid(t_pid_list **list, pid_t pid)
{
	t_pid_list	*nl;

	nl = (t_pid_list *)malloc(sizeof(t_pid_list));
	if (nl)
	{
		nl->pid = pid;
		nl->n = *list;
		*list = nl;
	}
	return ((nl == NULL) * PID_LIST_ERR_MEMALLOC);
}

void	destroy_pid_list(t_pid_list **list)
{
	while (*list)
		pop_pid(list);
}

void	pop_pid(t_pid_list **list)
{
	t_pid_list	*tmp;

	if (*list)
	{
		tmp = *list;
		*list = tmp->n;
		free(tmp);
	}
}

void	remove_pid(t_pid_list **list, pid_t pid)
{
	t_pid_list	*cur;
	t_pid_list	*prev;

	cur = *list;
	prev = NULL;
	while (cur && cur->pid != pid)
	{
		prev = cur;
		cur = cur->n;
	}
	if (cur)
	{
		if (prev == NULL)
			pop_pid(list);
		else
		{
			prev->n = cur->n;
			free(cur);
		}
	}
}
