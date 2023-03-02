/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:24:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/02 10:25:10 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_run_pipe(t_pipeline *ppl, char ***envp)
{
	int	ret;

	ret = 0;
	ret = pp_run_make_pipes(ppl);
	if (!ret)
		ret = pp_run_fork(ppl, envp);
	pp_run_close_pipes(ppl);
	pp_run_wait(ppl);
	return (ret);
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

void	pp_run_wait(t_pipeline *ppl)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	while (++i < ppl->cmd_nb)
		wait(&status);
}

int	pp_run_make_pipes(t_pipeline *ppl)
{
	int	i;

	errno = 0;
	ppl->pipefd = malloc(sizeof(int) * 2 * (ppl->cmd_nb - 1));
	if (NULL == ppl->pipefd)
		return (1);
	i = -1;
	while (++i < (ppl->cmd_nb - 1))
	{
		if (pipe(ppl->pipefd[i]) == -1)
			return (1);
	}
	return (0);
}

int	pp_run_fork(t_pipeline *ppl, char ***envp)
{
	int			i;
	pid_t		child;
	t_command	*cmd;

	i = -1;
	cmd = ppl->cmds;
	while (++i < ppl->cmd_nb)
	{
		child = fork();
		if (child == -1)
			return (1);
		else if (child == 0)
			pp_run_child(ppl, cmd, envp, i);
		cmd = cmd->next;
	}
	return (0);
}
