/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:28 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 09:11:54 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_export_isvalid(char *arg);
static int	ms_export_set(char *arg, char **envp, int index);

int	ms_export_run(t_msdata *msdata, t_command *cmd, int fd_out)
{
	int	i;

	(void)fd_out;
	i = 0;
	while (cmd->args[++i])
	{
		if (ms_export_arg(msdata, cmd->args[i]))
			return (1);
	}
	return (0);
}

int	ms_export_arg(t_msdata *msdata, char *arg)
{
	int		index;
	char	*tmp;

	if (!ms_export_isvalid(arg))
		return (ms_return_msg(1, arg, R_NVI));
	index = ms_env_getindex(msdata->envp, arg);
	if (index == -1)
	{
		tmp = ft_strdup(arg);
		if (tmp == NULL)
			return (ms_return_msg(1, NULL, R_STR));
		return (ms_utils_insert(tmp, &msdata->envp));
	}
	else
		return (ms_export_set(arg, msdata->envp, index));
}

static int	ms_export_isvalid(char *arg)
{
	int	i;

	if (ft_isdigit(arg[0]))
		return (0);
	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
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
