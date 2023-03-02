/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:46:23 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/02 10:26:31 by rertzer          ###   ########.fr       */
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
		ms_exit_msg(ppl, "syntax error");
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	errno = 0;
	fd = open(file->name, flags, mode);
	if (fd == -1)
		ms_exit_error(ppl, "open");
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
	if (ms_builtin_itis(cmd->cmd_path))
	{
		ms_builtin_run(ppl, cmd, envp);
		ms_exit_msg(ppl, NULL);
	}
	pp_check_cmd_path(ppl, cmd);
	if (NULL != cmd->cmd_path)
	{
		// il faut tout clean sauf une copie de lexec
		errno = 0;
		execve(cmd->cmd_path, cmd->args, *envp);
		ms_exit_error(ppl, cmd->cmd_path);
	}
}
