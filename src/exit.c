/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:55:38 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/08 10:14:09 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_msg(t_pipeline *ppl, char *msg)
{
	ms_pipeline_clean(ppl);
	if (msg)
	{
		if (msg[0] != 'Q')
			ft_putendl_fd(msg, 2);
		exit(1);
	}
	exit(0);
}

void	ms_exit_error(t_pipeline *ppl, char *msg)
{
	perror(msg);
	if (ppl)
		ms_pipeline_clean(ppl);
	exit(1);
}

int	ms_exit_run(t_command *cmd, char ***envp)
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
	exit(0);
}
