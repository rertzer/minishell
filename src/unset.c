/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:43:48 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 14:54:36 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_unset_run(t_msdata *msdata, t_command *cmd, int fd_out)
{
	int	index;

	(void)fd_out;
	index = ms_env_getindex(msdata->envp, cmd->args[1]);
	if (index < 0)
		return (0);
	free(msdata->envp[index]);
	while (msdata->envp[index])
	{
		msdata->envp[index] = msdata->envp[index + 1];
		index++;
	}
	return (0);
}
