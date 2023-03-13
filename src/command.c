/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:27:40 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/13 14:22:39 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_command_init(t_command *cmd);
static void	ms_command_clean_one(t_command *cmd);

int	ms_command_addback(t_command **start)
{
	t_command	*cmd;
	t_command	*last;

	errno = 0;
	cmd = malloc(sizeof(t_command));
	if (cmd == NULL)
		return (ms_return_error(errno, R_MAL));
	ms_command_init(cmd);
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

static void	ms_command_init(t_command *cmd)
{
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->cmd_path = NULL;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->cmd_nb = 0;
}

int	ms_command_clean(t_command **start)
{
	t_command	*tmp;
	t_command	*cmd;

	cmd = *start;
	while (cmd)
	{
		ms_command_clean_one(cmd);
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	*start = NULL;
	return (0);
}

static void	ms_command_clean_one(t_command *cmd)
{
	int	i;

	free(cmd->cmd_path);
	ms_command_close(cmd->fd_in);
	ms_command_close(cmd->fd_out);
	ms_tfile_clean(&cmd->infile);
	ms_tfile_clean(&cmd->outfile);
	i = -1;
	if (cmd->args)
	{
		while (cmd->args[++i])
			free(cmd->args[i]);
		free(cmd->args);
	}
}

void	ms_command_close(int fd)
{
	if (fd > 2)
		close(fd);
}
