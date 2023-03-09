/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:46:23 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 17:25:00 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_open_file(t_pipeline *ppl, t_file *file)
{
	int		flags;
	int		fd;
	mode_t	mode;

	if (file->mode == '=')
		return (pp_here_doc(ppl, file->name));
	else if (file->mode == '<')
		flags = O_RDONLY;
	else if (file->mode == '>')
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else if (file->mode == '?')
		flags = O_CREAT | O_APPEND | O_WRONLY;
	else
		ms_exit_msg(ppl, R_SYN);
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	errno = 0;
	fd = open(file->name, flags, mode);
	if (fd == -1)
		ms_exit_error(ppl, R_OPN);
	return (fd);
}

void	pp_open_in(t_pipeline *ppl, t_command *cmd, int i)
{
	t_file	*file;

	if (i != 0)
		cmd->fd_in = ppl->pipefd[i - 1][0];
	file = cmd->infile;
	while (file)
	{
		ms_command_close(cmd->fd_in);
		cmd->fd_in = pp_open_file(ppl, file);
		file = file->next;
	}
}

void	pp_open_out(t_pipeline *ppl, t_command *cmd, int i)
{
	t_file	*file;

	if (i != ppl->cmd_nb - 1)
		cmd->fd_out = ppl->pipefd[i][1];
	file = cmd->outfile;
	while (file)
	{
		ms_command_close(cmd->fd_out);
		cmd->fd_out = pp_open_file(ppl, file);
		file = file->next;
	}
}

void	pp_run_child(t_pipeline *ppl, t_command *cmd, char ***envp, int i)
{
	pp_open_in(ppl, cmd, i);
	pp_open_out(ppl, cmd, i);
	errno = 0;
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		ms_exit_error(ppl, "dup2");
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		ms_exit_error(ppl, "dup2");
	pp_run_close_pipes(ppl);
	if (cmd->cmd_path == NULL || cmd->cmd_path[0] == '\0')
		ms_exit_msg(ppl, NULL);
	if (ms_builtin_itis(cmd->cmd_path))
	{
		ms_builtin_run(cmd, envp);
		ms_exit_msg(ppl, NULL);
	}
	pp_run_exec(ppl, cmd, envp);
}

void	pp_run_exec(t_pipeline *ppl, t_command *cmd, char ***envp)
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
