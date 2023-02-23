/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:18:44 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 18:16:49 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_split_split(t_line *to_parse, int i, int j)
{
	int	ret;

	ret = 0;
	if (i != 0)
		ret = ms_split_middle(to_parse, quote, i, j);
	else
		ret = ms_split_beggin(to_parse, quote, i, j);
	return (ret);
}

int	ms_split_middle(t_line *to_parse, int i, int j)
{
	int		quote;
	char	*line;

	line = to_parse->line;
	quote = to_parse->line[i];
	to_parse->line = ft_strndup(line, i);
	if (to_parse->line == NULL)
		return (1);
	if (ft_strlen(line) == (unsigned long)(j + 1))
	{
		if (ms_split_addup(to_parse, &line[i + 1], quote, j - i - 1))
			return (1);
	}
	else
	{
		if (ms_split_addup(to_parse, &line[i + 1], quote, j - i - 1))
			return (1);
		if (ms_split_addup(to_parse, &line[j + 1], 0, ft_strlen(line) - j - 1))
			return (1);
		return (ms_parsing_quote(ms_line_last(to_parse)));
	}
	free(line);
	return (0);
}

int	ms_split_beggin(t_line *to_parse, int i, int j)
{
	int		ret;
	int		quote;
	char	*line;

	ret = 0;
	line = to_parse->line;
	quote = to_parse->line[i];
	to_parse->line = ft_strndup(&to_parse->line[1], j - 1);
	to_parse->quote = quote;
	if (ft_strlen(line) != (unsigned long)(j + 1))
	{
		if (ms_split_addup(to_parse, &line[j + 1], 0, ft_strlen(line) - j - 1))
			ret = 1;
		else
			ret = ms_parsing_quote(ms_line_last(to_parse));
	}
	free(line);
	return (ret);
}

int	ms_split_adddup(t_line *to_parse, char *line, int quote, int len)
{
	int		ret;
	char	*str;

	ret = 0;
	str = ft_strndup(line, len);
	if (str == NULL)
		ret = 1;
	else 
		ret = ms_line_addback(&to_parse, quote, str);
	return (ret);
}
