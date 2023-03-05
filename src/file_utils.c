/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:36:08 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/05 14:36:43 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

void	ms_file_mode(char *path, char *mode, int *shift)
{
	*mode = path[0];
	*shift = 1;
	if (path[0] == path[1])
	{
		(*mode)++;
		(*shift)++;
	}
}

int		ms_file_wordend(char *line, int j)
{
	int	word;

	word = 0;
	while (line[j])
	{
		if (ms_char_isin(line[j], FL_CHAR) && \
				ms_char_prevok(line, j))
		{
			if (word)
				break;
		}
		else
			word = 1;
		j++;
	}
	return (j);
}

t_file	**ms_file_adr(t_command *cmd, int mode)
{
	if (mode == 60 || mode == 61)
		return (&cmd->infile);
	else
		return (&cmd->outfile);
}

int	ms_file_chevron(t_command *cmd, int i)
{
	int		j;
	int		shift;
	char	mode;
	char	*str;
	ms_file_mode(&cmd->cmd_path[i], &mode, &shift);
	j = ms_file_wordend(cmd->cmd_path, i + shift);
	str = ft_strndup(&cmd->cmd_path[i + shift], j - i - shift);
	str = ms_char_unprotect(str);
	if (NULL == str)
		return (-1);
	ms_tfile_addback(ms_file_adr(cmd, mode), str, mode);
	while (i < j)
	{
		cmd->cmd_path[i] = ' ';
		i++;
	}
	return (i);
}
