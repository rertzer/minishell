/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:28 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/13 17:13:12 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_export_isposix(char *arg);
static int	ms_export_set(char *arg, char **envp, int index);

int	ms_export_run(t_command *cmd, char ***envp, int fd_out)
{
	int	i;

	(void)fd_out;
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

	if (!ms_export_isposix(arg))
		return (ms_return_msg(1, R_NVI));
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

static int	ms_export_isposix(char *arg)
{
	int	i;

	if (ft_isdigit(arg[0]))
		return (0);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!(ft_isdigit(arg[i]) || ft_isupper(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	ms_export_set(char *arg, char **envp, int index)
{
	free(envp[index]);
	envp[index] = ft_strdup(arg);
	return (0);
}
