/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:56:09 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 17:30:29 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parsing_start(char *line, char **envp)
{
	int		ret;
	t_line	*to_parse;

	to_parse = NULL;
	ret = ms_line_addback(&to_parse, 0, line);
	if (!ret)
		ret = ms_parsing_quote(to_parse);
	if (!ret)
		ret = ms_dollar_parse(to_parse, envp);
	if (!ret)
		ret = ms_pipe_start(to_parse);
	ret = ms_parsing_print(to_parse);
	ms_line_clean(to_parse);
	return (ret);
}

int	ms_parsing_quote(t_line *to_parse)
{
	int	i;
	int	j;
	int	ret;
	
	ret = 0;
	i = -1;
	while (to_parse->line[++i])
	{
		if (to_parse->line[i] == '"' || to_parse->line[i] == '\'')
		{
			j = ms_parsing_sec_quote(to_parse, i);
			if (j)
				ret = ms_split_split(to_parse, i, j);
		}
		if (ret)
			break ;
	}
	return (ret);
}

int	ms_parsing_sec_quote(t_line *to_parse, int i)
{
	char	quote;

	if (to_parse->quote)
		return (0);
	quote = to_parse->line[i];
	while (to_parse->line[++i])
	{
		if (to_parse->line[i] == quote)
			return (i);
	}
	return (0);
}

int	ms_parsing_print(t_line *line)
{
	while (line)
	{
		printf("quote : %c\nline: _%s_\n\n", line->quote, line->line);
		line = line->next;
	}
	return (0);
}
