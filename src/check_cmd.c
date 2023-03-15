/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:12:57 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/15 16:22:09 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pp_check_path(t_pipeline *ppl, t_command *cmd, \
		char **paths, char ***envp);
static void	pp_check_exit(t_pipeline *ppl, char **paths, char ***envp);

void	pp_check_cmd_path(t_pipeline *ppl, t_command *cmd, char ***envp)
{
	char	*pathlst;
	char	**paths;

	if (ms_builtin_itis(cmd->cmd_path) || ft_strchr(cmd->cmd_path, '/'))
		return ;
	pathlst = ms_env_getvalue(*envp, "PATH");
	paths = ft_split(pathlst, ':');
	if (pathlst)
		free(pathlst);
	if (paths == NULL)
		ms_exit_msg(ppl, envp, R_PAT);
	pp_check_path(ppl, cmd, paths, envp);
}

static void	pp_check_path(t_pipeline *ppl, t_command *cmd, \
		char **paths, char ***envp)
{
	int		i;
	char	*cmd_path;

	i = -1;
	cmd_path = NULL;
	while (paths[++i])
	{
		cmd_path = pp_pathjoin(paths[i], cmd->cmd_path);
		if (cmd_path == NULL)
			pp_check_exit(ppl, paths, envp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		pp_nullfree(&cmd_path);
	}
	ft_split_flush(paths);
	if (NULL == cmd_path)
		ms_exit_msg(ppl, envp, R_CMD);
	free(cmd->cmd_path);
	cmd->cmd_path = cmd_path;
}

static void	pp_check_exit(t_pipeline *ppl, char **paths, char ***envp)
{
	ft_split_flush(paths);
	ms_exit_msg(ppl, envp, R_QUT);
}
