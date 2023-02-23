/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:56:09 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 10:45:57 by rertzer          ###   ########.fr       */
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
		ret = ms_pipe_start(to_parse);
	ret = ms_parsing_print(to_parse);
	(void)envp;
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
				ret = ms_parsing_split(to_parse, i, j);
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

int	ms_parsing_split(t_line *to_parse, int i, int j)
{
	int		quote;
	char	*line;
	char	*str;
	
	quote = to_parse->line[i];
	line = to_parse->line;
	if (i != 0)
	{
		to_parse->line = ft_strndup(line, i);
		if (to_parse->line == NULL)
			return (1);
		if (ft_strlen(line) == (unsigned long)(j + 1))
		{
			str = ft_strndup(&line[i + 1], j - i - 1);
			if (str == NULL)
				return (1);
			if (ms_line_addback(&to_parse, quote, str))
				return (1);
		}
		else
		{
			str = ft_strndup(&line[i + 1], j - i - 1);
			if (str == NULL)
				return (1);
			if (ms_line_addback(&to_parse, quote, str))
				return (1);
			str = ft_strndup(&line[j + 1], ft_strlen(line) - j - 1);
			if (str == NULL)
				return (1);
			if (ms_line_addback(&to_parse, 0, str))
				return (1);
			return (ms_parsing_quote(ms_line_last(to_parse)));
		}
	}
	else
	{
		to_parse->line = ft_strndup(&to_parse->line[1], j - 1);
		to_parse->quote = quote;
		 if (ft_strlen(line) != (unsigned long)(j + 1))
		 {
			str = ft_strndup(&line[j + 1], ft_strlen(line) - j - 1);
		 	if (str == NULL)
				return (1);
		 	if (ms_line_addback(&to_parse, 0, str))
			 	return(1);
			return (ms_parsing_quote(ms_line_last(to_parse)));
		}
	}
	free(line);
	return (0);
}

int	ms_parsing_print(t_line *line)
{
	while (line)
	{
		printf("quote : %d\nline: %s\n\n", line->quote, line->line);
		line = line->next;
	}
	return (0);
}
