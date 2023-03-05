/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:13:25 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/05 14:34:29 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parsing_start(char *line, char ***envp)
{
	int		i;
	int 	j;
	char	*new_line;

	i = -1;
	j = 0;
	while (line[++i])
		j += ms_char_isin(line[i], SQ_CHAR);
	errno = 0;
	new_line = malloc(sizeof(char) * (i + j + 1));
	if (NULL == new_line)
		return (ms_return_error(errno, "malloc"));
	ms_parsing_quote(line, new_line);
	new_line = ms_dollar_parse(new_line, *envp);
	if (new_line == NULL)
		return (ms_return_error(errno, "parsing dollar"));
	return (ms_pipe_start(new_line, envp));
}

void	ms_parsing_quote(char *line, char *new_line)
{
	int		i;
	int		j;
	char	quote;

	i = -1;
	j = -1;
	quote = '\0';
	while (line[++i])
	{
		if (ms_parsing_isquote(&line[i], &quote))
			continue ;
		j++;
		if ((quote == '\'' && ms_char_isin(line[i], SQ_CHAR)) \
			|| (quote == '"' && ms_char_isin(line[i], DQ_CHAR)))
			new_line[j++] = '\\';
		new_line[j] = line[i];
	}
	new_line[j + 1] = '\0';
}

int	ms_parsing_isquote(char *line, char *quote)
{
	if (ms_char_isin(line[0], QT_CHAR))
	{
		if (*quote == line[0])
		{
			*quote = '\0';
			return (1);
		}
		else if ((!*quote) && ms_char_nextexist(line))
		{
			*quote = line[0];
			return (1);
		}
	}
	return (0);
}
