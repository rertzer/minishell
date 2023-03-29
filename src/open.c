/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:14:37 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/29 16:24:00 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pp_open_file(t_msdata *msdata, t_file *file);

void	pp_open_filelst(t_msdata *msdata, t_command *cmd, int i)
{
	t_file	*file;

	if (i != 0)
		cmd->fd_in = msdata->pipefd[i - 1][0];
	if (i != msdata->cmd_nb - 1)
		cmd->fd_out = msdata->pipefd[i][1];
	file = cmd->filelst;
	while (file)
	{
		if (file->mode == 60 || file->mode == 61)
		{
			ms_msdata_close(cmd->fd_in);
			cmd->fd_in = pp_open_file(msdata, file);
			if (file->mode == 61)
				unlink(file->name);
		}
		else
		{
			ms_msdata_close(cmd->fd_out);
			cmd->fd_out = pp_open_file(msdata, file);
		}
		file = file->next;
	}
}

static int	pp_open_file(t_msdata *msdata, t_file *file)
{
	int		flags;
	int		fd;
	mode_t	mode;

	if (file->name == NULL || file->name[0] == '\0')
		ms_exit_msg(msdata, R_SYN);
	flags = pp_open_flags(file->mode);
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	errno = 0;
	fd = open(file->name, flags, mode);
	if (fd == -1)
		ms_exit_error(msdata, file->name);
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
