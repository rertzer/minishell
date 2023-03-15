/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:13:34 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/15 15:23:11 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pp_child_dupfd(t_pipeline *ppl, t_command *cmd);
static void	pp_child_exec(t_pipeline *ppl, t_command *cmd, char ***envp);

void	pp_child_run(t_pipeline *ppl, t_command *cmd, char ***envp, int i)
{
	int	builtin;

	pp_open_in(ppl, cmd, i);
	pp_open_out(ppl, cmd, i);
	pp_child_dupfd(ppl, cmd);
	if (cmd->cmd_path == NULL || cmd->cmd_path[0] == '\0')
		ms_exit_msg(ppl, envp, NULL);
	builtin = ms_builtin_itis(cmd->cmd_path);
	if (builtin)
	{
		if (builtin != 7)
			ms_builtin_run(cmd, envp, 1);
		ms_exit_exit(ppl, envp, cmd->args[1]);
	}
	pp_child_exec(ppl, cmd, envp);
}

static void	pp_child_dupfd(t_pipeline *ppl, t_command *cmd)
{
	errno = 0;
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		ms_exit_error(ppl, "dup2");
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		ms_exit_error(ppl, "dup2");
	pp_run_close_pipes(ppl);
}

static void	pp_child_exec(t_pipeline *ppl, t_command *cmd, char ***envp)
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
