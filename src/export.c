/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:28 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 17:41:11 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_export_run(t_command *cmd, char ***envp)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		if (ms_export_arg(cmd->args[i], envp))
			return (1);
	}
	return (0);
}

int	ms_export_arg(char *arg, char ***envp)
{
	int		index;
	char	*tmp;

	index = ms_env_getindex(*envp, arg);
	if (index == -1)
	{
		tmp = ft_strdup(arg);
		if (tmp == NULL)
			return (ms_return_msg(1, R_STR));
		return (ms_utils_insert(tmp, envp));
	}
	else
		return (ms_export_set(arg, *envp, index));
}

int	ms_export_set(char *arg, char **envp, int index)
{
	free(envp[index]);
	envp[index] = ft_strdup(arg);
	return (0);
}
