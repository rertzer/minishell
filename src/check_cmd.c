/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:12:57 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 15:53:17 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pp_check_path(t_msdata *msdata, t_command *cmd, char **paths);
static void	pp_check_exit(t_msdata *msdata, char **paths);

void	pp_check_cmd_path(t_msdata *msdata, t_command *cmd)
{
	char	*pathlst;
	char	**paths;

	if (ms_builtin_itis(cmd->cmd_path) || ft_strchr(cmd->cmd_path, '/'))
		return ;
	pathlst = ms_env_getvalue(msdata->envp, "PATH");
	paths = ft_split(pathlst, ':');
	if (pathlst)
		free(pathlst);
	if (paths == NULL)
		ms_exit_msg(msdata, R_PAT);
	pp_check_path(msdata, cmd, paths);
}

static void	pp_check_path(t_msdata *msdata, t_command *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	i = -1;
	cmd_path = NULL;
	while (paths[++i])
	{
		cmd_path = pp_pathjoin(paths[i], cmd->cmd_path);
		if (cmd_path == NULL)
			pp_check_exit(msdata, paths);
		errno = 0;
		if (access(cmd_path, F_OK) == 0)
			break ;
		pp_nullfree(&cmd_path);
	}
	ft_split_flush(paths);
	if (NULL == cmd_path)
		ms_exit_path(msdata, cmd->cmd_path);
	free(cmd->cmd_path);
	cmd->cmd_path = cmd_path;
}

static void	pp_check_exit(t_msdata *msdata, char **paths)
{
	ft_split_flush(paths);
	ms_exit_msg(msdata, R_QUT);
}
