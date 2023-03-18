/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:55:38 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/18 12:24:54 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_msg(t_msdata *msdata, char *msg)
{
	ms_msdata_clean(msdata);
	ms_lpid_clean();
	if (msg)
	{
		if (msg[0] != 'Q')
			ft_putendl_fd(msg, 2);
		exit(1);
	}
	exit(0);
}

void	ms_exit_exit(t_msdata *msdata, char **args)
{
	if (args && args[0])
		ms_exit_resetstatus(msdata, args);
	ms_msdata_clean(msdata);
	ms_lpid_clean();
	ft_putendl_fd("exit", 1);
	exit(msdata->status);
}

void	ms_exit_error(t_msdata *msdata, char *msg)
{
	int	error;

	error = errno;
	perror(msg);
	if (error == 13)
		error = 126;
	ms_lpid_clean();
	ms_msdata_clean(msdata);
	exit(error);
}

void	ms_exit_child(t_msdata *msdata, char *path, char **args)
{
	int	error;

	error = errno;
	ft_putstr_fd("Minishell: ", 2);
	perror(path);
	if (error == 13)
		error = 126;
	if (error == 2)
		error = 127;
	free(path);
	ft_split_flush(args);
	ms_lpid_clean();
	ft_split_flush(msdata->envp);
	exit(error);
}

void	ms_exit_path(t_msdata *msdata, char *msg)
{
	ft_putstr_fd("Minishell : ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(": command not found\n", 2);
	ms_lpid_clean();
	ms_msdata_clean(msdata);
	exit(127);
}
