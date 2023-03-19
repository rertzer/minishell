/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_chevron.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:22:31 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 15:40:50 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ms_file_mode(char *path, char *mode, int *shift);
static int		ms_file_wordend(char *line, int j);
static t_file	**ms_file_adr(t_command *cmd, int mode);

int	ms_file_chevron(t_command *cmd, int i)
{
	int		end;
	int		shift;
	char	mode;
	char	*str;

	ms_file_mode(&cmd->cmd_path[i], &mode, &shift);
	end = ms_file_wordend(cmd->cmd_path, i + shift);
	str = ft_strndup(&cmd->cmd_path[i + shift], end - i - shift);
	str = ms_file_wildcard(str);
	str = ms_char_unprotect(str);
	if (NULL == str)
		return (-1);
	if (ms_char_isin(str[0], "<>"))
		return (ms_return_msg(-1, &str[0], R_SYN));
	ms_tfile_addback(ms_file_adr(cmd, mode), str, mode);
	while (i < end)
	{
		cmd->cmd_path[i] = ' ';
		i++;
	}
	return (i);
}

static void	ms_file_mode(char *path, char *mode, int *shift)
{
	*mode = path[0];
	*shift = 1;
	if (path[0] == path[1])
	{
		(*mode)++;
		(*shift)++;
	}
}

static int	ms_file_wordend(char *line, int j)
{
	int	word;

	word = 0;
	while (line[j])
	{
		if (ms_char_isin(line[j], FL_CHAR) && ms_char_prevok(line, j))
		{
			if (word)
				break ;
		}
		else
			word = 1;
		j++;
	}
	return (j);
}

static t_file	**ms_file_adr(t_command *cmd, int mode)
{
	if (mode == 60 || mode == 61)
		return (&cmd->infile);
	else
		return (&cmd->outfile);
}
