/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:13:25 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 16:33:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parsing_start(char *line, char ***envp, int status)
{
	int		len;
	char	*new_line;

	if (ms_utils_spaceonly(line))
		return (0);
	len = ms_parsing_computelen(line);
	errno = 0;
	new_line = malloc(sizeof(char) * (len + 1));
	if (NULL == new_line)
		return (ms_return_error(errno, R_MAL));
	ms_parsing_quote(line, new_line);
	new_line = ms_dollar_parse(new_line, *envp, status);
	if (new_line == NULL)
		return (1);
	return (ms_pipe_start(new_line, envp));
}

int	ms_parsing_computelen(char *line)
{
	int		len;
	int		extra;

	len = -1;
	extra = 0;
	while (line[++len])
		extra += ms_char_isin(line[len], SQ_CHAR);
	return (len + extra);
}

void	ms_parsing_quote(char *line, char *new_line)
{
	int		i;
	int		new_i;
	char	quote;

	i = -1;
	new_i = -1;
	quote = '\0';
	while (line[++i])
	{
		if (ms_parsing_isquote(&line[i], &quote))
			continue ;
		new_i++;
		if (ms_parsing_toprotect(quote, line[i]))
			new_line[new_i++] = '\\';
		new_line[new_i] = line[i];
	}
	new_line[new_i + 1] = '\0';
}

int	ms_parsing_toprotect(char quote, char c)
{
	if ((quote == '\'' && ms_char_isin(c, SQ_CHAR)) \
			|| (quote == '"' && ms_char_isin(c, DQ_CHAR)))
		return (1);
	return (0);
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
