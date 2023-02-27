/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:40:29 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/27 13:48:22 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pp_check_cmd_path(t_command *cmd)
{
	if ((!ms_builtin_itis(cmd->cmd_path)) && (!ft_strchr(cmd->cmd_path, '/')))
		return (pp_check_path(cmd));
	return (0);
}

int	pp_check_path(t_command *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	paths = ft_split(getenv("PATH"), ':');
	if (paths == NULL)
		return (1);
	i = -1;
	while (paths[++i])
	{
		cmd_path = pp_pathjoin(paths[i], cmd->cmd_path);
		if (cmd_path == NULL)
		{
			ft_split_flush(paths);
			return (1);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			break ;
		pp_nullfree(&cmd_path);
	}
	ft_split_flush(paths);
	if (NULL == cmd_path)
		return (1);
	cmd->cmd_path = cmd_path;
	return (0);
}
