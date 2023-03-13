/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:05:19 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/13 17:12:55 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_echo_isnflag(char *arg);
static void	ms_echo_print(char **args, int fd_out);

int	ms_echo_run(t_command *cmd, char ***envp, int fd_out)
{
	int	n_flag;

	(void)envp;
	n_flag = 0;
	if (cmd->args[1])
	{
		n_flag = ms_echo_isnflag(cmd->args[1]);
		ms_echo_print(&(cmd->args[n_flag]), fd_out);
	}
	if (n_flag == 0)
		ft_putchar_fd('\n', fd_out);
	return (0);
}

static int	ms_echo_isnflag(char *arg)
{
	if (ft_strcmp(arg, "-n") == 0)
		return (1);
	return (0);
}

static void	ms_echo_print(char **args, int fd_out)
{
	int	i;

	ft_putstr_fd(args[1], fd_out);
	i = 1;
	while (args[++i])
	{
		ft_putchar_fd(' ', fd_out);
		ft_putstr_fd(args[i], fd_out);
	}
}
