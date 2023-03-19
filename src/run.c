/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:15:03 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 13:04:36 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pp_run_make_pipes(t_msdata *msdata);
static int	pp_run_fork(t_msdata *msdata);

int	pp_run_pipe(t_msdata *msdata)
{
	int	ret;

	ret = 0;
	ret = pp_run_make_pipes(msdata);
	if (!ret)
		ret = pp_run_fork(msdata);
	pp_run_close_pipes(msdata);
	return (ret);
}

static int	pp_run_make_pipes(t_msdata *msdata)
{
	int	i;

	errno = 0;
	msdata->pipefd = malloc(sizeof(int) * 2 * (msdata->cmd_nb - 1));
	if (NULL == msdata->pipefd)
		return (ms_return_error(1, R_MAL));
	i = -1;
	while (++i < (msdata->cmd_nb - 1))
	{
		if (pipe(msdata->pipefd[i]) == -1)
			return (ms_return_error(1, R_PIP));
	}
	return (0);
}

static int	pp_run_fork(t_msdata *msdata)
{
	int			i;
	pid_t		child;
	t_command	*cmd;
	t_lpid		*lpid;

	i = -1;
	cmd = msdata->cmds;
	while (++i < msdata->cmd_nb)
	{
		errno = 0;
		child = fork();
		if (child == -1)
			return (ms_return_error(1, R_FRK));
		else if (child == 0)
			pp_child_run(msdata, cmd, i);
		else
		{
			lpid = ms_lpid_new(child);
			if (lpid == NULL)
				return (1);
			ms_lpid_add_back(lpid);
		}
		cmd = cmd->next;
	}
	return (0);
}

void	pp_run_close_pipes(t_msdata *msdata)
{
	int	i;

	i = -1;
	while (++i < (msdata->cmd_nb - 1))
	{
		close(msdata->pipefd[i][0]);
		close(msdata->pipefd[i][1]);
	}
}

int	pp_run_wait(void)
{
	int	status;

	status = 0;
	while (g_lpid && g_lpid->pid > 0)
	{
		waitpid(g_lpid->pid, &status, 0);
		if (g_lpid)
			ms_lpid_del_pid(g_lpid->pid);
	}
	return (WEXITSTATUS(status));
}
