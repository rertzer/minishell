/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:13:34 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 18:01:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pp_child_dupfd(t_msdata *msdata, t_command *cmd);
static void	pp_child_exec(t_msdata *msdata, t_command *cmd);

void	pp_child_run(t_msdata *msdata, t_command *cmd, int i)
{
	int	builtin;

	pp_open_in(msdata, cmd, i);
	pp_open_out(msdata, cmd, i);
	pp_child_dupfd(msdata, cmd);
	if (cmd->cmd_path == NULL || cmd->cmd_path[0] == '\0')
		ms_exit_msg(msdata, NULL);
	builtin = ms_builtin_itis(cmd->cmd_path);
	if (builtin)
	{
		if (builtin != 7)
		{
			ms_builtin_run(msdata, cmd, 1);
			ms_exit_exit(msdata, NULL);
		}
		ms_exit_exit(msdata, &(cmd->args[1]));
	}
	pp_child_exec(msdata, cmd);
}

static void	pp_child_dupfd(t_msdata *msdata, t_command *cmd)
{
	errno = 0;
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		ms_exit_error(msdata, "dup2");
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		ms_exit_error(msdata, "dup2");
	pp_run_close_pipes(msdata);
}

static void	pp_child_exec(t_msdata *msdata, t_command *cmd)
{
	char	*path;
	char	**args;

	pp_check_cmd_path(msdata, cmd);
	path = cmd->cmd_path;
	args = cmd->args;
	cmd->cmd_path = NULL;
	cmd->args = NULL;
	ms_pipeline_clean(msdata);
	if (NULL != path)
	{
		errno = 0;
		execve(path, args, msdata->envp);
		ms_exit_child(msdata, path, args);
	}
	exit(0);
}
