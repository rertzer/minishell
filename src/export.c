/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:28 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/11 10:41:36 by rertzer          ###   ########.fr       */
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
		return (ms_export_new(tmp, envp));
	}
	else
		return (ms_export_set(arg, *envp, index));
}

int	ms_export_new(char *arg, char ***envp)
{
	int		i;
	int		entries;
	char	**new_env;

	entries = 0;
	while (*envp && (*envp)[entries])
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
	envp[index] = ft_strdup(arg);
	return (0);
}
