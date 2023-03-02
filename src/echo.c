/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:05:19 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/02 10:19:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo_run(t_command *cmd, char ***envp)
{
	int	i;

	(void)envp;
	i = 0;
	while (cmd->args[++i])
	{
		if ( i > 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd->args[i], 1);
	}
	return (0);
}
