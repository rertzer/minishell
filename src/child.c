/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:13:34 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/13 17:03:23 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pp_child_run(t_pipeline *ppl, t_command *cmd, char ***envp, int i)
{
	pp_open_in(ppl, cmd, i);
	pp_open_out(ppl, cmd, i);
	pp_child_dupfd(ppl, cmd);
	if (cmd->cmd_path == NULL || cmd->cmd_path[0] == '\0')
		ms_exit_msg(ppl, envp, NULL);
	if (ms_builtin_itis(cmd->cmd_path))
	{
		ms_builtin_run(cmd, envp, 1);
		ms_exit_msg(ppl, envp, NULL);
	}
	pp_child_exec(ppl, cmd, envp);
}

void	pp_child_dupfd(t_pipeline *ppl, t_command *cmd)
{
	errno = 0;
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		ms_exit_error(ppl, "dup2");
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		ms_exit_error(ppl, "dup2");
	pp_run_close_pipes(ppl);
}

void	pp_child_exec(t_pipeline *ppl, t_command *cmd, char ***envp)
{
	char	*path;
	char	**args;

	pp_check_cmd_path(ppl, cmd, envp);
	path = cmd->cmd_path;
	args = cmd->args;
	cmd->cmd_path = NULL;
	cmd->args = NULL;
	ms_pipeline_clean(ppl);
	if (NULL != path)
	{
		errno = 0;
		execve(path, args, *envp);
		ms_exit_error(NULL, path);
	}
	exit(0);
}
