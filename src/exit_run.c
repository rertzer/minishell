/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:04:15 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/15 18:10:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_exit_cleanup(t_command *cmd, char ***envp);

int	ms_exit_run(t_command *cmd, char ***envp, int fd_out)
{
	int	status;

	status = 0;
	if (cmd && cmd->args[1])
	{
		if (ms_exit_getstatus(&(cmd->args[1]), &status))
			return (2);
	}
	else
		status = fd_out;
	ms_exit_cleanup(cmd, envp);
	exit(status);
}

static void	ms_exit_cleanup(t_command *cmd, char ***envp)
{
	if (cmd)
	{
		if (cmd->cmd_nb == 0)
		{
			ft_split_flush(*envp);
			*envp = NULL;
		}
		ms_command_clean(&cmd);
	}
	else
	{
		ft_split_flush(*envp);
		*envp = NULL;
	}
	ms_lpid_clean();
}
