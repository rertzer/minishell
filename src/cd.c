/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:19:46 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 14:50:49 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd_setpath(char *key, char *value, char ***envp)
{
	char	*tmp;

	tmp = ft_strjoin(key, value);
	if (tmp == NULL)
		return (ms_return_msg(1, R_STR));
	ms_export_arg(tmp, envp);
	return (0);
}

char	*ms_cd_resolvepath(char *path, char *pwd)
{
	char	*newpath;
	char	**dirlst;

	newpath = pp_pathjoin(pwd, path);
	if (newpath == NULL)
		return (NULL);
	dirlst = ft_split(newpath, '/');
	free(newpath);
	if (dirlst == NULL)
		return (ms_return_null(R_SPL));
	return (ms_cd_simplify(dirlst));
}

int	ms_cd_run(t_command *cmd, char ***envp)
{
	char	*path;
	char	*new_path;

	if (!cmd->args[1])
		return (0);
	path = ms_env_getvalue(*envp, "PWD");
	if (cmd->args[1][0] == '/')
		new_path = ft_strdup(cmd->args[1]);
	else
		new_path = ms_cd_resolvepath(cmd->args[1], path);
	if (new_path == NULL)
		return (ms_return_freeturn(&path, 1));
	errno = 0;
	if (chdir(new_path) == -1)
	{
		free(path);
		free(new_path);
		return (ms_return_error(errno, "chdir"));
	}
	ms_cd_setpath("OLDPWD=", path, envp);
	ms_cd_setpath("PWD=", new_path, envp);
	free(path);
	free(new_path);
	return (0);
}
