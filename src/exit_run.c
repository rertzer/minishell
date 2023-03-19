/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:04:15 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 11:19:04 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exit_cleanup(t_msdata *msdata, t_command *cmd);

int	ms_exit_run(t_msdata *msdata, t_command *cmd, int fd_out)
{
	(void)fd_out;
	if (cmd \
			&& cmd->args[1] \
			&& ms_exit_resetstatus(msdata, &(cmd->args[1])))
		return (2);
	ms_exit_cleanup(msdata, cmd);
	ft_putendl_fd("exit", 1);
	exit(msdata->status);
}

int	ms_exit_resetstatus(t_msdata *msdata, char **args)
{
	if (!ms_atoi(msdata, args[0]) && args[1] != NULL)
		return (ms_return_msg(2, "exit", R_TMA));
	return (0);
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

int	ms_exit_seterror(int error)
{
	if (error == 13)
		error = NOT_EXEC;
	if (error == 2)
		error = NOT_FOUND;
	return (error);
}
