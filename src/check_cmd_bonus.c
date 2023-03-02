/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:40:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/01 16:09:17 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pp_check_cmd_path(t_pipeline *ppl, t_command *cmd)
{
	char	**paths;

	if (ms_builtin_itis(cmd->cmd_path) || ft_strchr(cmd->cmd_path, '/'))
		return ;
	paths = ft_split(getenv("PATH"), ':');
	if (paths == NULL)
		ms_exit_msg(ppl, "PATH not found");
	pp_check_path(ppl, cmd, paths);
}

void	pp_check_path(t_pipeline *ppl, t_command *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (paths[++i])
	{
		cmd_path = pp_pathjoin(paths[i], cmd->cmd_path);
		if (cmd_path == NULL)
		{
			ft_split_flush(paths);
			ms_exit_msg(ppl, "malloc");
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		pp_nullfree(&cmd_path);
	}
	ft_split_flush(paths);
	if (NULL == cmd_path)
		ms_exit_msg(ppl, "command not found");
	free(cmd->cmd_path);
	cmd->cmd_path = cmd_path;
}
