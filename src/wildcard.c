/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:19:35 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/08 13:32:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_wildcard_start(char *pattern)
{
	DIR		*dd;
	char	*dir;

	if (ft_strchr(pattern, '*') == NULL)
		return (pattern);
	errno = 0;
	dir = getcwd(NULL, 0);
	if (dir == NULL)
		return (ms_return_nullerror("getcwd"));
	dd = opendir(dir);
	free(dir);
	if (dd == NULL)
		return (ms_return_nullerror("opendir"));
	pattern = ms_wildcard_expand(dd, pattern);
	closedir(dd);
	return (pattern);
}

char	*ms_wildcard_expand(DIR *dd, char *pattern)
{
	char			*str;
	struct dirent	*entry;

	str = NULL;
	errno = 0;
	entry = readdir(dd);
	while (entry)
	{
//		if (ms_wildcard_match(entry->d_name, pattern))
//			str = ms_wildcard_append(entry->d_name, str);
		fprintf(stderr, "file %s\n", entry->d_name);
		entry = readdir(dd);	
	}
	if (errno)
	{
		free(pattern);
		free(str);
		return (ms_return_nullerror("readdir"));
	}
	if (str == NULL)
		str = pattern;
	else
		free(pattern);
	return (str);
}

int	ms_wildcard_match(char *name, char *pattern)
{
	int		i;
	int		j;
	char	**patts;

	patts = ft_split(pattern, '*');
	if (patts == NULL)
		return (ms_return_msg(1, "R_SPL"));
	i = -1;
	j = 0;
	while (patts[++i])
	{
		j = ms_pattern_match(name, patts[i], j);
		if (j < 0)
			return (0);
	}
	return (1);
}
