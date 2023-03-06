/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:43:48 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 12:59:32 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_unset_run(t_command *cmd, char ***envp)
{
	int	index;

	index = ms_env_getindex(*envp, cmd->args[1]);
	if (index < 0)
		return (0);
	free((*envp)[index]);
	while ((*envp)[index])
	{
		(*envp)[index] = (*envp)[index + 1];
		index++;
	}
	return (0);
}
