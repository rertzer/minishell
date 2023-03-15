/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:55:38 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/15 15:23:38 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_msg(t_pipeline *ppl, char ***envp, char *msg)
{
	ms_pipeline_clean(ppl);
	ft_split_flush(*envp);
	ms_lpid_clean();
	*envp = NULL;
	if (msg)
	{
		if (msg[0] != 'Q')
			ft_putendl_fd(msg, 2);
		exit(1);
	}
	exit(0);
}

void	ms_exit_exit(t_pipeline *ppl, char ***envp, char *value)
{
	int	status;

	status = 0;
	if (value)
		status = ft_atoi(value);
	ms_pipeline_clean(ppl);
	ft_split_flush(*envp);
	ms_lpid_clean();
	*envp = NULL;
	exit(status);
}

void	ms_exit_error(t_pipeline *ppl, char *msg)
{
	ms_lpid_clean();
	perror(msg);
	if (ppl)
		ms_pipeline_clean(ppl);
	exit(1);
}

int	ms_exit_run(t_command *cmd, char ***envp, int fd_out)
{
	int	status;

	status = 0;
	if (cmd && cmd->args[1])
		status = ft_atoi(cmd->args[1]);
	(void)fd_out;
	ms_lpid_clean();
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
	exit(status);
}
