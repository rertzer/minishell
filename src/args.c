/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 13:32:08 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/26 16:17:38 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_args_add(t_command *cmd, char *line)
{
	int		i;
	int		arg_nb;
	char	**new;

	arg_nb = ms_args_getnb(cmd);
	new = malloc(sizeof(char *) * (arg_nb + 2));
	if (new == NULL)
		return (1);
	i = -1;
	while (++i < arg_nb)
		new[i] = cmd->args[i];
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
