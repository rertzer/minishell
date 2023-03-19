/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:32:08 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 15:27:46 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_args_fileparse(t_command *cmd);

int	ms_args_start(t_msdata *msdata)
{
	t_command	*tmp;

	tmp = msdata->cmds;
	while (tmp)
	{
		if (ms_args_fileparse(tmp))
			return (1);
		if (ms_args_argsparse(tmp))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	ms_args_fileparse(t_command *cmd)
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
		if (cmd->cmd_path[i] == '\0')
			break ;
	}
	return (0);
}

int	ms_args_getnb(t_command *cmd)
{
	int	nb;

	if (cmd->args == NULL)
		return (0);
	nb = 0;
	while (cmd->args[nb] != NULL)
		nb++;
	return (nb);
}

int	ms_args_insert(t_command *cmd, char *word)
{
	word = ms_char_unprotect(word);
	if (word == NULL)
		return (1);
	if (cmd->cmd_path == NULL)
	{	
		errno = 0;
		cmd->cmd_path = ft_strdup(word);
		if (NULL == cmd->cmd_path)
		{
			free(word);
			return (ms_return_error(1, R_STR));
		}
	}
	if (ms_args_add(cmd, word))
	{
		free(word);
		return (1);
	}
	return (0);
}

int	ms_args_add(t_command *cmd, char *line)
{
	int		i;
	int		arg_nb;
	char	**new;

	if (line == NULL)
		return (1);
	arg_nb = ms_args_getnb(cmd);
	errno = 0;
	new = malloc(sizeof(char *) * (arg_nb + 2));
	if (new == NULL)
		return (ms_return_error(1, R_MAL));
	i = -1;
	while (++i < arg_nb)
		new[i] = cmd->args[i];
	new[i] = line;
	new[++i] = NULL;
	free(cmd->args);
	cmd->args = new;
	return (0);
}
