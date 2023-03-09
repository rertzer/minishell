/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:04:49 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/09 11:31:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_inset(const char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ms_get_start(char const *str)
{
	size_t	start;
	char	prev;

	start = 0;
	prev = '\0';
	while (str[start] && prev != '\\' && ms_inset(str[start], " \t"))
	{
		prev = str[start];
		start++;
	}
	return (start);
}

static int	ms_get_end(char const *str)
{
	size_t	end;

	end = ft_strlen(str) - 1;
	while (end != 0 && str[end - 1] != '\\' && ms_inset(str[end], " \t"))
		end--;
	return (end);
}

char	*ms_trim_trim(char *line)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimed;

	start = ms_get_start(line);
	end = ms_get_end(line);
	if (start > end)
		len = 0;
	else
		len = end - start + 1;
	errno = 0;
	trimed = malloc(sizeof(char) * (len + 1));
	if (trimed == NULL)
		return (ms_return_null(R_MAL));
	i = -1;
	while (++i < len)
		trimed[i] = line[start + i];
	trimed[i] = '\0';
	free(line);
	return (trimed);
}
