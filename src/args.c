/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:32:08 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/13 13:34:33 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_args_add(t_command *cmd, char *line)
{
	int		i;
	int		arg_nb;
	char	**new;

	arg_nb = ms_args_getnb(cmd);
	errno = 0;
	new = malloc(sizeof(char *) * (arg_nb + 2));
	if (new == NULL)
		return (ms_return_error(errno, R_MAL));
	i = -1;
	while (++i < arg_nb)
		new[i] = cmd->args[i];
	if (line == NULL)
	{
		free(new);
		return (1);
	}
	new[i] = line;
	new[++i] = NULL;
	free(cmd->args);
	cmd->args = new;
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
			return (ms_return_error(errno, R_STR));
		}
	}
	ms_args_add(cmd, word);
	return (0);
}
