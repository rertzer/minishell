/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:04:49 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 18:22:13 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ms_trim_getstart(char const *str);
static int		ms_trim_getend(char const *str);
static size_t	ms_trim_getlen(int start, int end);
static int		ms_trim_inset(const char c, char const *set);

char	*ms_trim_trim(char *line)
{
	size_t	i;
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimed;

	start = ms_trim_getstart(line);
	end = ms_trim_getend(line);
	len = ms_trim_getlen(start, end);
	errno = 0;
	trimed = malloc(sizeof(char) * (len + 1));
	if (trimed == NULL)
	{
		free(line);
		return (ms_return_nullerror(R_MAL));
	}
	i = -1;
	while (++i < len)
		trimed[i] = line[start + i];
	trimed[i] = '\0';
	free(line);
	return (trimed);
}

static int	ms_trim_getstart(char const *str)
{
	size_t	start;
	char	prev;

	start = 0;
	prev = '\0';
	while (str[start] && prev != '\\' && ms_trim_inset(str[start], " \t"))
	{
		prev = str[start];
		start++;
	}
	return (start);
}

static int	ms_trim_getend(char const *str)
{
	size_t	end;

	end = ft_strlen(str);
	if (end)
		end--;
	while (end > 0 && str[end - 1] != '\\' && ms_trim_inset(str[end], " \t"))
		end--;
	return (end);
}

static size_t	ms_trim_getlen(int start, int end)
{
	if (start > end)
		return (0);
	return (end - start + 1);
}

static int	ms_trim_inset(const char c, char const *set)
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
