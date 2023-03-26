/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:43:48 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/23 17:32:01 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_unset_unset(t_msdata *msdata, char *arg);

int	ms_unset_run(t_msdata *msdata, t_command *cmd, int fd_out)
{
	int	i;

	(void)fd_out;
	i = 0;
	while (cmd->args[++i])
		ms_unset_unset(msdata, cmd->args[i]);
	return (0);
}

static void	ms_unset_unset(t_msdata *msdata, char *arg)
{
	int	index;

	if (ms_char_isin('=', arg))
		return ;
	index = ms_env_getindex(msdata->envp, arg);
	if (index < 0)
		return ;
	free(msdata->envp[index]);
	while (msdata->envp[index])
	{
		msdata->envp[index] = msdata->envp[index + 1];
		index++;
	}
}
