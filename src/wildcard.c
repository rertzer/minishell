/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:19:35 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 18:48:43 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ms_wildcard_expand(DIR *dd, char *pattern);
static int	ms_wildcard_export(struct dirent *entry,	\
		char *pattern, char ***expanded);
static char	**ms_wildcard_returnclean(char *pattern, \
		char **expanded, char *msg);

char	**ms_wildcard_start(char *pattern)
{
	DIR		*dd;
	char	*dir;
	char	**expanded;

	expanded = NULL;
	if (ft_strchr(pattern, '*') == NULL)
	{
		ms_utils_insert(pattern, &expanded);
		return (expanded);
	}
	errno = 0;
	dir = NULL;//getcwd(NULL, 0);
	if (dir == NULL)
		return (ms_wildcard_returnclean(pattern, expanded, "getcwd"));
	dd = opendir(dir);
	free(dir);
	if (dd == NULL)
		return (ms_wildcard_returnclean(pattern, expanded, "opendir"));
	expanded = ms_wildcard_expand(dd, pattern);
	closedir(dd);
	return (expanded);
}

static char	**ms_wildcard_expand(DIR *dd, char *pattern)
{
	char			**expanded;
	struct dirent	*entry;

	errno = 0;
	entry = readdir(dd);
	expanded = NULL;
	while (entry)
	{
		if (ms_wildcard_export(entry, pattern, &expanded))
			return (NULL);
		entry = readdir(dd);
	}
	if (errno)
		ms_wildcard_returnclean(pattern, expanded, "readdir");
	if (expanded == NULL)
	{
		if (ms_utils_insert(pattern, &expanded))
			return (NULL);
	}
	else
		free(pattern);
	return (expanded);
}

static int	ms_wildcard_export(struct dirent *entry,	\
		char *pattern, char ***expanded)
{
	int	ret;

	ret = ms_backtrack_backtrack('\0', pattern, entry->d_name);
	if (ret > 0)
		ret = ms_utils_insert(ft_strdup(entry->d_name), expanded);
	return (ret);
}

static char	**ms_wildcard_returnclean(char *pattern, char **expanded, \
		char *msg)
{
	free(pattern);
	if (expanded)
		ft_split_flush(expanded);
	ft_putstr_fd("minishell : error :", 2);
	return (ms_return_null2error(msg));
}
