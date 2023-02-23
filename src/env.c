/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:46:42 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 17:02:37 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			break ;
		}
	}
	return (value);
}

int	ms_env_valueindex(char *env, char *key)
{
	int i;

	i = 0;
	while (env[i] && env[i] == key[i])
		i++;
	if (env[i] == '=' && key[i] == '\0')
		return (i + 1);
	return (0);
}
