/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zanikin <zanikin@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 01:37:47 by zanikin           #+#    #+#             */
/*   Updated: 2024/08/09 05:16:55 by zanikin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <sys/_types/_pid_t.h>
#include <sys/_types/_size_t.h>
#include <sys/semaphore.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "pid_list/pid_list.h"
#include "logger/logger.h"
#include "logger/error_codes.h"
#include "philosopher/t_philo.h"
#include "remap/remap.h"
#include "config.h"
#include "remap/t_sem_init.h"

void		dest_philosopher_func(void);
int			init_philosopher_func(int *error);
int			philosopher(void *philo);

static void	set_philo(t_philo *philo, size_t i);
static int	create_philosopher(t_philo *philo, t_pid_list **pids);
static int	wait_philosophers(t_pid_list **pids, int *error);

void		test_leaks(void);

int	awake_philosophers(t_conf *conf)
{
	int					error;
	t_philo				philo;
	const t_sem_init	sem_init = {"philosophers_forks", conf->nop};
	size_t				i;
	t_pid_list			*pids;

	error = 0;
	pids = NULL;
	if (!(init_philosopher_func(&error) || sem_open_r(&philo.s, &sem_init,
				PHILOSOPHER_ERR_BEGIN, &error)))
	{
		conf->stt = gettime() + 500000;
		philo.conf = conf;
		i = 0;
		while (!error && i < conf->nop)
		{
			set_philo(&philo, i++);
			error = create_philosopher(&philo, &pids);
		}
		wait_philosophers(&pids, &error);
	}
	sem_close(philo.s);
	sem_unlink(sem_init.name);
	dest_philosopher_func();
	return (error);
}

static void	set_philo(t_philo *philo, size_t i)
{
	philo->i = i;
	philo->id = i + 1;
	philo->te[0] = philo->conf->stt;
	philo->te[1] = philo->te[0] + philo->conf->te;
	philo->tec = philo->te + (philo->id % 2);
	philo->ttd = philo->conf->stt + philo->conf->td;
	philo->conf = philo->conf;
	philo->ate = 0;
}

static int	create_philosopher(t_philo *philo, t_pid_list **pids)
{
	pid_t	pid;
	int		error;
	int		tmp_error;

	pid = fork();
	if (pid > 0)
	{
		error = 0;
		push_pid(pids, pid);
	}
	else if (pid == 0)
	{
		tmp_error = 0;
		destroy_pid_list(pids);
		error = philosopher(philo);
		sem_close(philo->s);
		destroy_logger(0);
		if (tmp_error && !error)
			error = tmp_error;
		test_leaks();
		exit(error);
	}
	else
		error = (errno == EAGAIN) * PHILOSOPHER_ERR_PROC_LIM
			+ (errno != EAGAIN) * PHILOSOPHER_ERR_PROC_MEM;
	return (error);
}

static int	wait_philosophers(t_pid_list **pids, int *error)
{
	pid_t	pid;
	int		status;

	pid = 0;
	while (!*error && pid != -1 && *pids)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1 && errno == EINTR)
			pid = 0;
		if (pid > 0)
		{
			remove_pid(pids, pid);
			if (WIFEXITED(status))
				*error = WEXITSTATUS(status);
		}
	}
	while (*pids)
	{
		kill(pids[0]->pid, SIGKILL);
		waitpid(pids[0]->pid, &status, 0);
		pop_pid(pids);
	}
	return (*error);
}
