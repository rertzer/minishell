/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:04:32 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/05 11:39:15 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	ms_pipex_start(t_line *parsed, char ***envp)
{
	int			cmd_nb;
	t_command	*cmd;
	t_command	*cmd_start;

	cmd_nb = 1;
	cmd_start = NULL;
	if (ms_command_addback(&cmd_start))
		return (1);
	cmd_start->cmd_nb = 1;
	cmd = cmd_start;
	while (parsed)
	{
		if (ms_pipex_pipe(parsed, &cmd, &cmd_start, &cmd_nb))
				return (1);
		parsed = parsed->next;
	}
	return (ms_pipeline_run(cmd_start, cmd_nb, envp));
}

int	ms_pipex_pipe(t_line *parsed, t_command **cmd, t_command **cmd_start, \
				int *cmd_nb)
{
	if (parsed->quote == 'p')
	{
		if (ms_command_addback(cmd))
			return (ms_command_clean(cmd_start));
		*cmd = (*cmd)->next;
		(*cmd_nb)++;
		(*cmd)->cmd_nb = *cmd_nb;
	}
	else
	{
		if (ms_pipex_parse(parsed, *cmd))
			return (ms_command_clean(cmd_start));
	}
	return (0);
}

int	ms_pipex_parse(t_line *parsed, t_command *cmd)
{
	if (parsed->quote == 60 || parsed->quote == 61)
		return (ms_tfile_addback(&cmd->infile, parsed));
	if (parsed->quote == 62 || parsed->quote == 63)
		return (ms_tfile_addback(&cmd->outfile, parsed));
	else if (parsed->quote == '\'' || parsed->quote == '"')
		return (ms_pipex_word(parsed->line, cmd));
	return (ms_pipex_other(parsed, cmd));
}

int	ms_pipex_word(char *line, t_command *cmd)
{
	if (cmd->cmd_path == NULL)
		cmd->cmd_path = ft_strdup(line);
	return (ms_args_add(cmd, line));
}

int	ms_pipex_other(t_line *parsed, t_command *cmd)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	word = NULL;
	while (parsed->line[i])
	{
		len = ms_utils_wordlen(&parsed->line[i]);
		if (len)
		{
			word = ft_strndup(&parsed->line[i], len);
			if (word == NULL || ms_pipex_word(word, cmd))
				return (ms_return_freeturn(&word, 1));
		}
		else
			len = 1;
		i += len;
	}
	return (0);
}
*/
int	ms_pipex_print(t_command *cmd_start, int cmd_nb)
{
	// remove function for submission
	printf("%d commands\n", cmd_nb);
	while (cmd_start)
	{
		printf("\ncmd %s\n", cmd_start->cmd_path);
		t_file	*file;
		file = cmd_start->infile;
		while (file)
		{
			printf("file_in: _%s_ %c\n", file->name, file->mode);
			file = file->next;
		}
		file = cmd_start->outfile;
		while (file)
		{
			printf("file_out: _%s_ %c\n", file->name, file->mode);
			file = file->next;
		}
		if (cmd_start->args)
		{
			int i = -1;
			while (cmd_start->args[++i])
				printf("arg %s\n", cmd_start->args[i]);
		}
		cmd_start = cmd_start->next;
	}
	return (0);
}
