/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:32:08 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 17:22:40 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_args_add(t_command *cmd, char *line)
{
	int		i;
	int		arg_nb;
	char	**new;

	arg_nb = ms_args_getnb(cmd);
	errno = 0;
	new = malloc(sizeof(char *) * (arg_nb + 2));
	if (new == NULL)
		return (ms_return_error(errno, R_MAL));
	i = -1;
	while (++i < arg_nb)
		new[i] = cmd->args[i];
	new[i] = line;
	new[++i] = NULL;
	free(cmd->args);
	cmd->args = new;
	return (0);
}

int	ms_args_getnb(t_command *cmd)
{
	int	nb;

	if (cmd->args == NULL)
		return (0);
	nb = 0;
	while (cmd->args[nb] != NULL)
		nb++;
	return (nb);
}

int	ms_args_parse(t_command *cmd)
{
	if (cmd->cmd_path == NULL || ms_utils_spaceonly(cmd->cmd_path))
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
		return (0);
	}
	return (ms_args_parseloop(cmd, -1, 0, 0));
}

int	ms_args_parseloop(t_command *cmd, int i, int start, int word)
{
	char	*line;

	line = cmd->cmd_path;
	cmd->cmd_path = NULL;
	while (line[++i])
	{
		if (ms_char_isin(line[i], SP_CHAR) && ms_char_prevok(line, i))
		{
			if (word)
			{
				if (ms_args_insert(cmd, ft_strndup(&line[start], i - start)))
					return (ms_return_freeturn(&line, 1));
				start = i + 1;
				word = 0;
			}
		}
		else
			word = 1;
	}
	if (i != start && word)
	{
		if (ms_args_insert(cmd, ft_strndup(&line[start], i - start)))
			return (ms_return_freeturn(&line, 1));
	}
	return (ms_return_freeturn(&line, 0));
}

int	ms_args_insert(t_command *cmd, char *line)
{
	char	*str;

	line = ms_char_unprotect(line);
	if (line == NULL)
		return (1);
	if (cmd->cmd_path == NULL)
	{	
		errno = 0;
		str = ft_strdup(line);
		if (NULL == str)
		{
			free(line);
			return (ms_return_error(errno, R_STR));
		}
		cmd->cmd_path = str;
	}
	ms_args_add(cmd, line);
	return (0);
}
