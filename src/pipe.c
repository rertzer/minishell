/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:25:09 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 17:56:39 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_pipe_cmdinit(t_msdata *msdata, char *line);
static int	ms_pipe_split(t_msdata *msdata, t_command *cmd);
static int	ms_pipe_cut(t_command *cmd, char *line, int *start, int *i);
static int	ms_pipe_error(t_msdata *msdata);

int	ms_pipe_start(t_msdata *msdata, char *line)
{
	msdata->cmd_nb = 1;
	if (ms_pipe_cmdinit(msdata, line))
		return (1);
	if (ms_pipe_split(msdata, msdata->cmds))
		return (ms_pipe_error(msdata));
	if (ms_args_start(msdata))
		return (ms_pipe_error(msdata));
	return (ms_pipeline_start(msdata));
}

static int	ms_pipe_cmdinit(t_msdata *msdata, char *line)
{
	if (ms_command_addback(&msdata->cmds))
		return (ms_return_freeturn(&line, 1));
	msdata->cmds->cmd_nb = 1;
	msdata->cmds->cmd_path = line;
	return (0);
}

static int	ms_pipe_split(t_msdata *msdata, t_command *cmd)
{
	int		i;
	int		start;
	char	*line;

	line = ft_strdup(cmd->cmd_path);
	if (line == NULL)
		return (ms_return_msg(1, NULL, R_STR));
	i = -1;
	start = 0;
	while (line[++i])
	{
		if (line[i] == '|' && ms_char_prevok(line, i))
		{
			if (line[i + 1] == '|')
				line[i + 1] = ' ';
			if (ms_pipe_cut(cmd, line, &start, &i))
				return (ms_return_freeturn(&line, 1));
			msdata->cmd_nb++;
			cmd = cmd->next;
			cmd->cmd_nb = msdata->cmd_nb;
		}
	}
	free(line);
	return (0);
}

static int	ms_pipe_cut(t_command *cmd, char *line, int *start, int *i)
{
	if (ms_command_addback(&cmd))
		return (1);
	free(cmd->cmd_path);
	cmd->cmd_path = ft_strndup(&line[*start], *i - *start);
	if (NULL == cmd->cmd_path)
		return (ms_return_msg(1, NULL, R_STR));
	if (ms_utils_spaceonly(cmd->cmd_path))
		return (ms_return_msg(1, "|", R_SYN));
	*start = *i + 1;
	cmd = cmd->next;
	cmd->cmd_path = ft_strndup(&line[*start], ft_strlen(&line[*start]));
	if (NULL == cmd->cmd_path)
		return (ms_return_msg(1, NULL, R_STR));
	return (0);
}

static int	ms_pipe_error(t_msdata *msdata)
{
	ms_command_clean(msdata);
	return (2);
}
