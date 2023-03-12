/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:16:20 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 13:09:04 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_file_start(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ms_file_parse(tmp))
			return (1);
		if (ms_args_parse(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	ms_file_parse(t_command *cmd)
{
	int		i;

	i = -1;
	while (cmd->cmd_path[++i])
	{
		if ((cmd->cmd_path[i] == '>' || cmd->cmd_path[i] == '<') \
				&& ms_char_prevok(cmd->cmd_path, i))
			i = ms_file_chevron(cmd, i);
		if (i < 0)
			return (1);
	}
	return (0);
}
