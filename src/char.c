/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:21:15 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/30 14:51:21 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_char_isin(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	ms_char_nextexist(char *line)
{
	char	c;

	c = line[0];
	while (*line++)
	{
		if (*line == c)
			return (1);
	}
	return (0);
}

int	ms_char_prevok(char *line, int i)
{
	if (i && (line[i - 1] == '\\'))
		return (0);
	if (i == 0)
		return (1);
	i--;
	while (i && !ms_char_isin(line[i], HD_CHAR))
		i--;
	while (i && ms_char_isin(line[i], SP_CHAR))
		i--;
	if (i && line[i] == '<' && line[i - 1] == '<')
		return (0);
	return (1);
}

char	*ms_char_unprotect(char *line)
{
	int	i;
	int	j;

	if (line == NULL)
		return (NULL);
	line = ms_trim_trim(line);
	if (line == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '\\' || line[i] == '\001')
			continue ;
		line[j] = line[i];
		j++;
	}
	line[j] = '\0';
	return (line);
}
