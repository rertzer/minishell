/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:14:37 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 17:16:56 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pp_open_file(t_msdata *msdata, t_file *file);

void	pp_open_in(t_msdata *msdata, t_command *cmd, int i)
{
	t_file	*file;

	if (i != 0)
		cmd->fd_in = msdata->pipefd[i - 1][0];
	file = cmd->infile;
	while (file)
	{
		ms_command_close(cmd->fd_in);
		cmd->fd_in = pp_open_file(msdata, file);
		file = file->next;
	}
}

void	pp_open_out(t_msdata *msdata, t_command *cmd, int i)
{
	t_file	*file;

	if (i != msdata->cmd_nb - 1)
		cmd->fd_out = msdata->pipefd[i][1];
	file = cmd->outfile;
	while (file)
	{
		ms_command_close(cmd->fd_out);
		cmd->fd_out = pp_open_file(msdata, file);
		file = file->next;
	}
}

static int	pp_open_file(t_msdata *msdata, t_file *file)
{
	int		flags;
	int		fd;
	mode_t	mode;

	if (file->mode == '=')
		return (pp_here_doc(msdata, file->name));
	flags = pp_open_flags(file->mode);
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	errno = 0;
	fd = open(file->name, flags, mode);
	if (fd == -1)
		ms_exit_error(msdata, R_OPN);
	return (fd);
}

int	pp_open_flags(char mode)
{
	int	flags;

	flags = 0;
	if (mode == '<')
		flags = O_RDONLY;
	else if (mode == '>')
		flags = O_CREAT | O_TRUNC | O_WRONLY;
	else if (mode == '?')
		flags = O_CREAT | O_APPEND | O_WRONLY;
	return (flags);
}
