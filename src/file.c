/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:10:44 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/01 12:13:04 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_file_parse(t_line *to_parse)
{
	while (to_parse)
	{
		if (!to_parse->quote)
		{
			if (ms_file_parseline(&to_parse))
				return (1);
		}
		to_parse = to_parse->next;
	}
	return (0);
}

int	ms_file_parseline(t_line **to_parse)
{
	int	i;

	i = -1;
	while ((*to_parse)->line[++i])
	{
		if (ms_file_chevron(to_parse, i, '<'))
			return (1);
		else if (ms_file_chevron(to_parse, i, '>'))
			return (1);
	}
	return (0);
}

int	ms_file_chevron(t_line **to_parse, int i, char chevron)
{
	int	shift;

	shift = 1;
	if ((*to_parse)->line[i] == chevron)
	{
		if ((*to_parse)->line[i + 1] == chevron)
		{
			shift++;
			chevron++;
		}
		while ((*to_parse)->line[i + shift] && \
				((*to_parse)->line[i + shift] == '\t' || \
				(*to_parse)->line[i + shift] == ' '))
			shift++;
		return (ms_file_split(to_parse, chevron, i, shift));
	}
	return (0);
}

int	ms_file_quotenext(t_line **to_parse, char chevron)
{
	if ((*to_parse)->next && (((*to_parse)->next->quote == '\'') \
			 || ((*to_parse)->next->quote == '"')))
		(*to_parse)->next->quote = chevron;
	else
		return (1);
	 return (0);
}

int	ms_file_addin(t_line **to_parse, char *line, char chevron)
{
	if (ms_line_addin(*to_parse, line))
		return (1);
	(*to_parse)->next->quote = chevron;
	return (0);
}
