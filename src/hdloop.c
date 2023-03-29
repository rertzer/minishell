/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdloop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:29:50 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/29 16:20:56 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_hdloop_handlefile(t_file *file, int hdcount);
static char	*ms_hdloop_getfilename(int hdcount);

int	ms_hdloop_start(t_msdata *msdata)
{
	int			ret;
	int			hdcount;
	t_command	*cmd;
	t_file		*file;

	hdcount = 0;
	cmd = msdata->cmds;
	while (cmd)
	{
		file = cmd->filelst;
		while (file)
		{
			ret = ms_hdloop_handlefile(file, hdcount);
			if (ret == -1)
				return (1);
			hdcount += ret;
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

static int	ms_hdloop_handlefile(t_file *file, int hdcount)
{
	char	*filename;

	if (file->mode == '=')
	{
		filename = ms_hdloop_getfilename(hdcount);
		if (filename == NULL)
			return (-1);
		if (pp_here_doc(file->name, filename))
			return (-1);
		free(file->name);
		file->name = filename;
		return (1);
	}
	return (0);
}

static char	*ms_hdloop_getfilename(int hdcount)
{
	char	*filename;
	char	*number;

	number = ft_uxitoa(hdcount, "0123456789");
	if (number == NULL)
		return (ms_return_null(R_STR));
	filename = ft_strjoin(HD_PATH, number);
	free(number);
	if (filename == NULL)
		return (ms_return_null(R_STR));
	return (filename);
}
