/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:13:25 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 17:51:53 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_parsing_computelen(char *line);
static void	ms_parsing_quote(char *line, char *new_line);
static int	ms_parsing_isquote(char *line, char *quote);
static int	ms_parsing_toprotect(char quote, char c);

int	ms_parsing_start(t_msdata *msdata, char *line)
{
	int		len;
	char	*new_line;

	if (ms_utils_spaceonly(line))
		return (0);
	len = ms_parsing_computelen(line);
	errno = 0;
	new_line = malloc(sizeof(char) * (len + 1));
	if (NULL == new_line)
		return (ms_return_error(1, R_MAL));
	ms_parsing_quote(line, new_line);
	new_line = ms_dollar_parse(msdata, new_line);
	if (new_line == NULL)
		return (1);
	return (ms_pipe_start(msdata, new_line));
}

static int	ms_parsing_computelen(char *line)
{
	int		len;
	int		extra;

	len = -1;
	extra = 0;
	while (line[++len])
		extra += ms_char_isin(line[len], SQ_CHAR);
	return (len + extra);
}

static void	ms_parsing_quote(char *line, char *new_line)
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

static int	ms_parsing_isquote(char *line, char *quote)
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

static int	ms_parsing_toprotect(char quote, char c)
{
	if ((quote == '\'' && ms_char_isin(c, SQ_CHAR)) \
			|| (quote == '"' && ms_char_isin(c, DQ_CHAR)))
		return (1);
	return (0);
}
