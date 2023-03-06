/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:55:38 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 17:39:13 by rertzer          ###   ########.fr       */
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
	if (cmd->cmd_nb == 0)
	{
		ft_split_flush(*envp);
		*envp = NULL;
	}
	ms_command_clean(&cmd);
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
