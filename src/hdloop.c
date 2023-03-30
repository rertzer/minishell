/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdloop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:29:50 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/30 14:23:10 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_hdloop_handlefile(t_file *file);

int	ms_hdloop_start(t_msdata *msdata)
{
	t_command	*cmd;
	t_file		*file;

	cmd = msdata->cmds;
	while (cmd)
	{
		file = cmd->filelst;
		while (file)
		{
			if (ms_hdloop_handlefile(file))
				return (1);
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

static int	ms_hdloop_handlefile(t_file *file)
{
	if (file->mode == '=')
	{
		file->fd = pp_here_doc(file->name);
		if (file->fd == 0)
			return (1);
	}
	return (0);
}
