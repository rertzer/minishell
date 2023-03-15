/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:05:19 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/15 09:33:34 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_echo_isnflag(char **arg);
static void	ms_echo_print(char **args, int fd_out);

int	ms_echo_run(t_command *cmd, char ***envp, int fd_out)
{
	int	n_flag;

	(void)envp;
	n_flag = 0;
	if (cmd->args[1])
	{
		n_flag = ms_echo_isnflag(&(cmd->args[1]));
		ms_echo_print(&(cmd->args[1 + n_flag]), fd_out);
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', fd_out);
	return (0);
}

static int	ms_echo_isnflag(char **args)
{
	int	i;
	
	i = -1;
	while (args[++i])
	{
		if (args[i][0] != '-' || !ms_utils_isonly(&(args[i][1]), 'n'))
			break;
	}
	return (i);
}

static void	ms_echo_print(char **args, int fd_out)
{
	int	i;

	if (args[0] == NULL)
		return ;
	ft_putstr_fd(args[0], fd_out);
	i = 0;
	while (args[++i])
	{
		ft_putchar_fd(' ', fd_out);
		ft_putstr_fd(args[i], fd_out);
	}
}
