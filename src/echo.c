/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:05:19 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/09 15:27:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo_run(t_command *cmd, char ***envp)
{
	int	i;
	int n_flag;

	(void)envp;
	n_flag = 0;
	i = 0;
	if (cmd->args[1])
	{
		if (cmd->args[1][0] == '-' && cmd->args[1][1] == 'n')
		{
			n_flag = 1;
			i++;
		}
		while (cmd->args[++i])
		{
			if ((i > 1 && n_flag == 0) || i > 2)
				ft_putchar_fd(' ', 1);
			ft_putstr_fd(cmd->args[i], 1);
		}
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
