/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:19:35 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/09 11:31:16 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_wildcard_start(char *pattern)
{
	DIR		*dd;
	char	*dir;
	char	**expanded;

	expanded = NULL;
	if (ft_strchr(pattern, '*') == NULL)
	{
		ms_export_new(pattern, &expanded);
		return (expanded);
	}
	pattern = ms_pattern_anchor(pattern);
	errno = 0;
	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		ms_return_error(1, "getcwd");
		return (NULL);
	}
	dd = opendir(dir);
	free(dir);
	if (dd == NULL)
	{
		ms_return_error(1, "opendir");
		return (NULL);
	}
	expanded = ms_wildcard_expand(dd, pattern);
	closedir(dd);
	return (expanded);
}

char	**ms_wildcard_expand(DIR *dd, char *pattern)
{
	int				ret;
	char			**expanded;
	struct dirent	*entry;

	errno = 0;
	entry = readdir(dd);
	expanded = NULL;
	while (entry)
	{
		ret = ms_wildcard_match(entry->d_name, pattern);
		if (ret > 0)
		{
			if (ms_export_new(ft_strdup(entry->d_name), &expanded))
			return (NULL);
		}
		else if (ret < 0)
			return (NULL);
		entry = readdir(dd);	
	}
	if (errno)
	{
		free(pattern);
		ft_split_flush(expanded);
		ms_return_error(1, "readdir");
		return (NULL);
	}
	if (expanded == NULL && ms_export_new(pattern, &expanded))
		return (NULL);
	else
		free(pattern);
	return (expanded);
}
/*
char	*ms_wildcard_append(char **exp_tab, char *name)
{
	char	*tmp;

	tmp = NULL;
	if (s1 == NULL)
	{
		tmp = ft_strdup(s2);
		if (tmp == NULL)
			return (ms_return_null(R_STR));
		return (tmp);
	}
	tmp = ft_strjoin(s1, " ");
	if (tmp == NULL)
		return (ms_return_null(R_STR));
	free(s1);
	s1 = ft_strjoin(tmp, s2);
	if (s1 == NULL)
		return (ms_return_null(R_STR));
	free(tmp);
	return (s1);
}*/

int	ms_wildcard_match(char *name, char *pattern)
{
	int		i;
	int		j;
	char	**patts;
	char	*name_cpy;

	name_cpy = ft_strdup(name);
	if (name_cpy == NULL)
		return (ms_return_msg(-1, R_STR));
	name_cpy = ms_pattern_anchor(name_cpy);
	if (name_cpy == NULL)
		return (-1);
	patts = ft_split(pattern, '*');
	if (patts == NULL)
		return (ms_return_msg(-1, "R_SPL"));
	i = -1;
	j = 0;
	while (patts[++i])
	{
		j = ms_pattern_match(name_cpy, patts[i], j);
		if (j < 0)
			return (0);
	}
	return (1);
}
