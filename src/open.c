/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:14:37 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 16:39:24 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_open_file(t_pipeline *ppl, t_file *file, char ***envp)
{
	int		flags;
	int		fd;
	mode_t	mode;

	if (file->mode == '=')
		return (pp_here_doc(ppl, file->name));
	flags = pp_open_flags(file->mode, ppl, envp);
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	errno = 0;
	fd = open(file->name, flags, mode);
	if (fd == -1)
		ms_exit_error(ppl, R_OPN);
	return (fd);
}

int	pp_open_flags(char mode, t_pipeline *ppl, char ***envp)
{
	int	flags;

	flags = 0;
	if (mode == '<')
		flags = O_RDONLY;
	else if (mode == '>')
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else if (mode == '?')
		flags = O_CREAT | O_APPEND | O_WRONLY;
	else
		ms_exit_msg(ppl, envp, R_SYN);
	return (flags);
}

void	pp_open_in(t_pipeline *ppl, t_command *cmd, int i, char ***envp)
{
	t_file	*file;

	if (i != 0)
		cmd->fd_in = ppl->pipefd[i - 1][0];
	file = cmd->infile;
	while (file)
	{
		ms_command_close(cmd->fd_in);
		cmd->fd_in = pp_open_file(ppl, file, envp);
		file = file->next;
	}
}

void	pp_open_out(t_pipeline *ppl, t_command *cmd, int i, char ***envp)
{
	t_file	*file;

	if (i != ppl->cmd_nb - 1)
		cmd->fd_out = ppl->pipefd[i][1];
	file = cmd->outfile;
	while (file)
	{
		ms_command_close(cmd->fd_out);
		cmd->fd_out = pp_open_file(ppl, file, envp);
		file = file->next;
	}
}
