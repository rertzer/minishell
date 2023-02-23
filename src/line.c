/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 14:57:00 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 14:34:54 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_line_addback(t_line **first, char quote, char *str)
{
	t_line	*line;
	t_line	*last;

	errno = 0;
	line = malloc(sizeof(t_line));
	if (line == NULL)
		return (errno);
	line->quote = quote;
	line->line = str;
	line->next = NULL;
	if (*first == NULL)
		*first = line;
	else
	{
		last = *first;
		while (last->next)
			last = last->next;
		last->next = line;
	}
	return (0);
}

int	ms_line_addin(t_line *prev, char *str)
{
	t_line	*line;

	errno = 0;
	line = malloc(sizeof(t_line));
	if (line == NULL)
		return (errno);
	line->quote = 0;
	line->line = str;
	line->next = prev->next;
	prev->next = line;
	return (0);
}

char	*ms_line_extractnext(t_line *prev)
{
	char	*str;
	t_line	*tmp;

	str = prev->next->line;
	tmp = prev->next->next;
	free(prev->next);
	prev->next = tmp;
	return (str);
}

t_line	*ms_line_last(t_line *first)
{
	t_line	*last;

	last = first;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

void ms_line_clean(t_line *first)
{
	t_line	*tmp;
	t_line	*next;
	
	tmp = first;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->line);
		free(tmp);
		tmp = next;
	}
}
