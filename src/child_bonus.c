/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:46:23 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/27 17:48:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_open_file(t_file *file, int *fd)
{
	int		flags;
	mode_t	mode;

	if (file->mode == '<')
		flags = O_RDONLY;
	else if (file->mode == '=')
	{
		if (pp_here_doc(file->name, fd))
			return (1);
		return (0);
	}
	else if (file->mode == '>')
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else if (file->mode == '?')
		flags = O_CREAT | O_APPEND | O_WRONLY;
	else
		return (1);
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	errno = 0;
	*fd = open(file->name, flags, mode);
	if (*fd == -1)
		return (1);
	return (0);
}

int	pp_open_in(t_pipeline *ppl, t_command *cmd, int *fd_in, int i)
{
	t_file	*file;

	if (i != 0)
		*fd_in = ppl->pipefd[i - 1][0];
	else
		*fd_in = 0;
	file = cmd->infile;
	while (file)
	{
		if (*fd_in > 2)
			close(*fd_in);
		if (pp_open_file(file, fd_in))
			return (1);
		file = file->next;
	}
	return (0);
}

int	pp_open_out(t_pipeline *ppl, t_command *cmd, int *fd_out, int i)
{
	t_file	*file;

	if (i != ppl->cmd_nb - 1)
		*fd_out = ppl->pipefd[i][1];
	else
		*fd_out = 1;
	file = cmd->outfile;
	while (file)
	{
		if (*fd_out > 2)
			close(*fd_out);
		if (pp_open_file(file, fd_out))
			return (1);
		file = file->next;
	}
	return (0);
}

int	pp_run_child(t_pipeline *ppl, t_command *cmd, char **envp, int i)
{
	int		fd_in;
	int		fd_out;

	if (pp_open_in(ppl, cmd, &fd_in, i))
		exit (1);
	if (pp_open_out(ppl, cmd, &fd_out, i))
		exit (1);
	errno = 0;
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit (1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit (1);
	pp_run_close_pipes(ppl);
	if (ms_builtin_itis(cmd->cmd_path))
		exit (ms_builtin_run(cmd, envp));
	if (pp_check_cmd_path(cmd))
		exit (1);
	else if (NULL != cmd->cmd_path)
		execve(cmd->cmd_path, cmd->args, envp);
	close(fd_in);
	close(fd_out);
	exit (1);
}
