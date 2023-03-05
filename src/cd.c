/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:19:46 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/05 18:06:33 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd_setpath(char *key, char *value, char ***envp)
{
	char	*tmp;

	tmp = ft_strjoin(key, value);
	if (tmp == NULL)
		return (1);
	ms_export_arg(tmp, envp);
	return (0);
}

int	ms_cd_pathsplit(char *path, char **npath, char **syml)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (path[++i])
	{
		if (path[i] == '/' && path[i + 1])
			j = i;
	}
	if (j > 0)
	{
		*npath = ft_strndup(path, j);
		if (*npath == NULL)
			return (1);
		*syml = ft_strdup(&path[j]);
		if (*syml == NULL)
			return (1);
	}
	else
	{
		*npath = NULL;
		*syml = path;
	}
	return (0);
}

char	*ms_cd_symbolicpath(char *path)
{
	char		*npath;
	char		*syml;
	struct stat	sb;

	syml = NULL;
	npath = NULL;
	if (lstat(path, &sb) == -1)
	{
		perror("lstat");
		return (NULL);
	}
	if (((sb.st_mode & S_IFMT) == S_IFLNK))
	{
		if (ms_cd_pathsplit(path, &npath, &syml))
			return (NULL);
		if (npath)
		{
			if (chdir(npath) == -1)
				return (NULL);
			free(npath);
		}
		npath = getcwd(NULL, 0);
		if (chdir(syml) == -1)
			return (NULL);
		if (npath)
			return (pp_pathjoin(npath, syml));
	}
	else
		if (chdir(path) == -1)
			return (NULL);
	return (getcwd(NULL, 0));
}

int	ms_cd_run(t_command *cmd, char ***envp)
{
	char		*path;

	path = ms_env_getvalue(*envp, "PWD");
	ms_cd_setpath("OLDPWD=", path, envp);
	errno = 0;
	free(path);
	path = ms_cd_symbolicpath(cmd->args[1]);
	if (path == NULL)
		return (1);
	ms_cd_setpath("PWD=", path, envp);
	free(path);
	return (0);
}
