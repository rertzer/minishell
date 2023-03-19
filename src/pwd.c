/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:41:14 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/19 09:18:04 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd_run(t_msdata *msdata, t_command *cmd, int fd_out)
{
	char	*buffer;

	(void)cmd;
	buffer = ms_env_getvalue(msdata->envp, "PWD");
	if (buffer == NULL)
		return (ms_return_msg(1, NULL, R_PAT));
	ft_putendl_fd(buffer, fd_out);
	free(buffer);
	return (0);
}
