/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:27:40 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/27 14:54:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_command_addback(t_command **start)
{
	t_command	*cmd;
	t_command	*last;

	cmd = malloc(sizeof(t_command));
	if (cmd == NULL)
		return (1);
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->cmd_path = NULL;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->cmd_nb = 0;
	if (*start == NULL)
		*start = cmd;
	else
	{
		last = *start;
		while (last->next)
			last = last->next;
		last->next = cmd;
	}
	return (0);
}

int	ms_command_clean(t_command **start)
{
	int			i;
	t_command	*tmp;
	t_command	*cmd;

	tmp = *start;
	while (cmd)
	{
		ms_tfile_clean(&cmd->infile);
		ms_tfile_clean(&cmd->outfile);
		free(cmd->cmd_path);
		i = -1;
		if (cmd->args)
		{
			while (cmd->args[++i])
				free(cmd->args[i]);
			free(cmd->args);
		}
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	*start = NULL;
	return (0);
}
