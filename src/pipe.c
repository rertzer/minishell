/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:09 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 17:26:47 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipe_start(char *line, char ***envp)
{
	int			cmd_nb;
	t_command	*cmd_start;

	cmd_nb = 1;
	cmd_start = NULL;
	if (ms_command_addback(&cmd_start))
		return (1);
	cmd_start->cmd_nb = 1;
	cmd_start->cmd_path = line;
	if (ms_pipe_split(cmd_start, &cmd_nb))
		return (ms_command_clean(&cmd_start));
	if (ms_file_start(cmd_start))
		return (ms_command_clean(&cmd_start));
	return (ms_pipeline_run(cmd_start, cmd_nb, envp));
}

int	ms_pipe_split(t_command *cmd, int *cmd_nb)
{
	int		i;
	int		start;
	char	*line;

	line = ft_strdup(cmd->cmd_path);
	i = -1;
	start = 0;
	while (line[++i])
	{
		if (line[i] == '|' && ms_char_prevok(line, i))
		{
			if (ms_pipe_cut(cmd, line, &start, &i))
				break ;
			(*cmd_nb)++;
			cmd->cmd_nb = *cmd_nb;
		}
	}
	free(line);
	return (0);
}

int	ms_pipe_cut(t_command *cmd, char *line, int *start, int *i)
{
	if (ms_command_addback(&cmd))
		return (1);
	free(cmd->cmd_path);
	cmd->cmd_path = ft_strndup(&line[*start], *i - *start);
	if (NULL == cmd->cmd_path)
		return (1);
	*start = *i + 1;
	cmd = cmd->next;
	cmd->cmd_path = ft_strndup(&line[*start], ft_strlen(&line[*start]));
	if (NULL == cmd->cmd_path)
		return (1);
	return (0);
}
