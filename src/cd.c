/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:19:46 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 13:49:56 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*ms_cd_setroot(void);
static char		*ms_cd_resolvepath(char *path, char *pwd);
static int		ms_cd_chdir(char *new_path);
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
	if (ms_utils_isonly(cmd->args[1], '/'))
		new_path = ms_cd_setroot();
	else
		new_path = ms_cd_resolvepath(cmd->args[1], path);
	if (new_path == NULL)
		return (ms_cd_return(1, path, new_path));
	if (ms_cd_chdir(new_path))
		return (ms_cd_return(1, path, new_path));
	ms_cd_setpath(msdata, "OLDPWD=", path);
	ms_cd_setpath(msdata, "PWD=", new_path);
	return (ms_cd_return(0, path, new_path));
}

static char	*ms_cd_setroot(void)
{
	char	*new_path;

	new_path = ft_strdup("/");
	if (new_path == NULL)
		return (ms_return_null(R_STR));
	return (new_path);
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

static int	ms_cd_chdir(char *new_path)
{
	errno = 0;
	if (chdir(new_path) == -1)
		return (ms_return_error(2, new_path));
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
