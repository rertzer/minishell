/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:04:15 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 17:15:00 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exit_cleanup(t_msdata *msdata, t_command *cmd);

int	ms_exit_run(t_msdata *msdata, t_command *cmd, int fd_out)
{
	if (cmd && cmd->args[1])
	{
		if (ms_exit_getstatus(msdata, &(cmd->args[1])))
			return (2);
	}
	else
		msdata->status = fd_out;
	ms_exit_cleanup(msdata, cmd);
	exit(msdata->status);
}

static void	ms_exit_cleanup(t_msdata *msdata, t_command *cmd)
{
	if (cmd)
	{
		if (cmd->cmd_nb == 0)
		{
			ft_split_flush(msdata->envp);
			msdata->envp = NULL;
		}
		ms_command_clean(msdata);
	}
	else
	{
		ft_split_flush(msdata->envp);
		msdata->envp = NULL;
	}
	ms_lpid_clean();
}
