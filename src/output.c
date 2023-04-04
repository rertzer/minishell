/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:13:36 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/30 15:08:35 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_output_openfile(t_file *file);

int	ms_output_openall(t_command *cmd)
{
	int		fd;
	t_file	*file;

	fd = 1;
	file = cmd->filelst;
	while (file)
	{
		if (file->mode == 60 || file->mode == 61)
			ms_msdata_close(cmd->fd_in);
		else
			ms_msdata_close(cmd->fd_out);
		if (file->mode == 61)
			fd = pp_here_doc(file->name);
		else
			fd = ms_output_openfile(file);
		if (fd == -1)
			break ;
		file = file->next;
	}
	return (fd);
}

static int	ms_output_openfile(t_file *file)
{
	int		flags;
	int		fd;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	flags = pp_open_flags(file->mode);
	errno = 0;
	fd = open(file->name, flags, mode);
	if (fd == -1)
		return (ms_return_error(-1, file->name));
	return (fd);
}
