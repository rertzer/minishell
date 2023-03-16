/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:15:03 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/15 18:40:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pp_run_make_pipes(t_pipeline *ppl);
static int	pp_run_fork(t_pipeline *ppl, char ***envp);

int	pp_run_pipe(t_pipeline *ppl, char ***envp)
{
	int	ret;

	ret = 0;
	ret = pp_run_make_pipes(ppl);
	if (!ret)
		ret = pp_run_fork(ppl, envp);
	pp_run_close_pipes(ppl);
	return (ret);
}

static int	pp_run_make_pipes(t_pipeline *ppl)
{
	int	i;

	errno = 0;
	ppl->pipefd = malloc(sizeof(int) * 2 * (ppl->cmd_nb - 1));
	if (NULL == ppl->pipefd)
		return (ms_return_error(errno, R_MAL));
	i = -1;
	while (++i < (ppl->cmd_nb - 1))
	{
		if (pipe(ppl->pipefd[i]) == -1)
			return (ms_return_error(errno, R_PIP));
	}
	return (0);
}

static int	pp_run_fork(t_pipeline *ppl, char ***envp)
{
	int			i;
	pid_t		child;
	t_command	*cmd;

	i = -1;
	cmd = ppl->cmds;
	while (++i < ppl->cmd_nb)
	{
		errno = 0;
		child = fork();
		if (child == -1)
			return (ms_return_error(errno, R_FRK));
		else if (child == 0)
			pp_child_run(ppl, cmd, envp, i);
		else
			ms_lpid_add_back(ms_lpid_new(child));
		cmd = cmd->next;
	}
	return (0);
}

void	pp_run_close_pipes(t_pipeline *ppl)
{
	int	i;

	i = -1;
	while (++i < (ppl->cmd_nb - 1))
	{
		close(ppl->pipefd[i][0]);
		close(ppl->pipefd[i][1]);
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
