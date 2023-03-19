/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:55:38 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 11:10:05 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_msg(t_msdata *msdata, char *msg)
{
	ms_msdata_clean(msdata);
	ms_lpid_clean();
	if (msg)
	{
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
	exit(msdata->status);
}

void	ms_exit_error(t_msdata *msdata, char *msg)
{
	int	error;

	perror(msg);
	error = ms_exit_seterror(errno);
	ms_lpid_clean();
	ms_msdata_clean(msdata);
	exit(error);
}

void	ms_exit_child(t_msdata *msdata, char *path, char **args)
{
	int	error;

	ft_putstr_fd("minishell: ", 2);
	perror(path);
	error = ms_exit_seterror(errno);
	free(path);
	ft_split_flush(args);
	ms_lpid_clean();
	ft_split_flush(msdata->envp);
	exit(error);
}

void	ms_exit_path(t_msdata *msdata, char *msg)
{
	ms_return_msg(1, msg, R_CMD);
	ms_lpid_clean();
	ms_msdata_clean(msdata);
	exit(NOT_FOUND);
}
