/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:58:07 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 15:56:16 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_args_parseloop(t_command *cmd, char *line);
static int	ms_args_isseparator(char *line, int i);
static int	ms_args_expinsert(t_command *cmd, char **expanded);
static int	ms_args_wildinsert(t_command *cmd, char *line, int start, int i);

int	ms_args_argsparse(t_command *cmd)
{
	char	*line;

	if (cmd->cmd_path == NULL || ms_utils_spaceonly(cmd->cmd_path))
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
		return (0);
	}
	line = cmd->cmd_path;
	cmd->cmd_path = NULL;
	return (ms_args_parseloop(cmd, line));
}

static int	ms_args_parseloop(t_command *cmd, char *line)
{
	int	end;
	int	start;
	int	in_word;

	end = -1;
	start = 0;
	in_word = 0;
	while (line[++end])
	{
		if (ms_args_isseparator(line, end))
		{
			if (in_word)
			{
				if (ms_args_wildinsert(cmd, line, start, end))
					return (ms_return_freeturn(&line, 1));
				start = end + 1;
				in_word = 0;
			}
		}
		else
			in_word = 1;
	}
	if (end != start && in_word && ms_args_wildinsert(cmd, line, start, end))
		return (ms_return_freeturn(&line, 1));
	return (ms_return_freeturn(&line, 0));
}

static int	ms_args_isseparator(char *line, int i)
{
	if (ms_char_isin(line[i], SP_CHAR) && ms_char_prevok(line, i))
		return (1);
	return (0);
}

static int	ms_args_wildinsert(t_command *cmd, char *line, int start, int i)
{
	char	*word;
	char	**expanded;

	word = ft_strndup(&line[start], i - start);
	if (word == NULL)
		return (ms_return_msg(1, NULL, R_STR));
	expanded = ms_wildcard_start(word);
	if (expanded == NULL)
		return (1);
	ms_sort_sort(expanded);
	if (ms_args_expinsert(cmd, expanded))
		return (1);
	free(expanded);
	return (0);
}

static int	ms_args_expinsert(t_command *cmd, char **expanded)
{
	int	i;

	i = -1;
	while (expanded[++i])
	{
		if (ms_args_insert(cmd, expanded[i]))
		{
			while (expanded[++i])
				free(expanded[i]);
			free(expanded);
			return (1);
		}
	}
	return (0);
}
