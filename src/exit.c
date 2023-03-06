/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:55:38 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 12:58:41 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_msg(t_pipeline *ppl, char *msg)
{
	ms_pipeline_clean(ppl);
	if (msg)
	{
		ft_putendl_fd(msg, 2);
		exit(1);
	}
	exit(0);
}

void	ms_exit_error(t_pipeline *ppl, char *msg)
{
	perror(msg);
	ms_pipeline_clean(ppl);
	exit(1);
}


int	ms_exit_run(t_command *cmd, char ***envp)
{
	ms_command_clean(&cmd);
	ft_split_flush(*envp);
	*envp = NULL;
	exit(0);
}
