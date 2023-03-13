/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:46:42 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/13 11:52:20 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_env_valueindex(char *env, char *key);

int	ms_env_run(t_command *cmd, char ***envp)
{
	int	i;

	(void)cmd;
	i = -1;
	while ((*envp)[++i])
		ft_putendl_fd((*envp)[i], 1);
	return (0);
}

char	*ms_env_getvalue(char **envp, char *key)
{
	int		i;
	int		index;
	char	*value;

	value = NULL;
	i = -1;
	while (envp[++i] != NULL)
	{
		index = ms_env_valueindex(envp[i], key);
		if (index)
		{
			value = ft_strdup(&envp[i][index]);
			if (value == NULL)
				return (ms_return_null(R_STR));
			break ;
		}
	}
	return (value);
}

int	ms_env_getindex(char **envp, char *key)
{
	int		i;
	int		index;

	i = -1;
	while (envp[++i] != NULL)
	{
		index = ms_env_valueindex(envp[i], key);
		if (index)
			return (i);
	}
	return (-1);
}

static int	ms_env_valueindex(char *env, char *key)
{
	int	i;

	i = 0;
	while (env[i] && key[i] != '=' && env[i] == key[i])
		i++;
	if (env[i] == '=' && (key[i] == '\0' || key[i] == '='))
		return (i + 1);
	return (0);
}
