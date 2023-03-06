/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:28 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 15:13:32 by rertzer          ###   ########.fr       */
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
	int	index;

	index = ms_env_getindex(*envp, arg);
	if (index == -1)
		return (ms_export_new(arg, envp));
	else
		return (ms_export_set(arg, *envp, index));
}

int	ms_export_new(char *arg, char ***envp)
{
	int		i;
	int		entries;
	char	**new_env;

	entries = 0;
	while ((*envp)[entries])
		entries++;
	errno = 0;
	new_env = malloc(sizeof(char *) * (entries + 2));
	if (new_env == NULL)
		return (ms_return_error(errno, R_MAL));
	i = -1;
	while (++i < entries)
		new_env[i] = (*envp)[i];
	new_env[i] = arg;
	new_env[i + 1] = NULL;
	free(*envp);
	*envp = new_env;
	return (0);
}

int	ms_export_set(char *arg, char **envp, int index)
{
	free(envp[index]);
	envp[index] = arg;
	return (0);
}
