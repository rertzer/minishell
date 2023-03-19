/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:19:46 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 09:29:16 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ms_cd_isroot(char *path);
static char		*ms_cd_resolvepath(char *path, char *pwd);
static int		ms_cd_chdir(char *path, char *new_path);
static int		ms_cd_setpath(t_msdata *msdata, char *key, char const *value);

int	ms_cd_run(t_msdata *msdata, t_command *cmd, int fd_out)
{
	char	*path;
	char	*new_path;

	(void)fd_out;
	if (!cmd->args[1])
		return (0);
	if (cmd->args[2])
		return (ms_return_msg(1, cmd->args[2], R_SNP));
	path = ms_env_getvalue(msdata->envp, "PWD");
	if (ms_cd_isroot(cmd->args[1]))
			new_path = ft_strdup("/");
	else
		new_path = ms_cd_resolvepath(cmd->args[1], path);
	if (new_path == NULL)
		new_path = ft_strdup("/");
	if (ms_cd_chdir(path, new_path))
		return (1);
	ms_cd_setpath(msdata, "OLDPWD=", path);
	ms_cd_setpath(msdata, "PWD=", new_path);
	free(path);
	free(new_path);
	return (0);
}

static int	ms_cd_isroot(char *path)
{
	if (ms_utils_isonly(path, '/'))
		return (1);
	return (0);
}

static char	*ms_cd_resolvepath(char *path, char *pwd)
{
	char	*newpath;
	char	**dirlst;

	if (path[0] == '/')
		newpath = ft_strdup(path);
	else
		newpath = pp_pathjoin(pwd, path);
	if (newpath == NULL)
		return (NULL);
	dirlst = ft_split(newpath, '/');
	free(newpath);
	if (dirlst == NULL)
		return (ms_return_null(R_SPL));
	return (ms_cd_simplify(dirlst));
}

static int	ms_cd_chdir(char *path, char *new_path)
{
	errno = 0;
	if (chdir(new_path) == -1)
	{
		perror(new_path);
		free(path);
		free(new_path);
		return (2);
	}
	return (0);
}

static int	ms_cd_setpath(t_msdata *msdata, char *key, char const *value)
{
	char	*tmp;

	if (value == NULL)
		tmp = ft_strdup("");
	else
		tmp = ft_strjoin(key, value);
	if (tmp == NULL)
		return (ms_return_msg(1, NULL, R_STR));
	ms_export_arg(msdata, tmp);
	free(tmp);
	return (0);
}
