/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:41:14 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/13 17:08:19 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd_run(t_command *cmd, char ***envp, int fd_out)
{
	char	*buffer;

	(void)cmd;
	buffer = ms_env_getvalue(*envp, "PWD");
	if (buffer == NULL)
		return (ms_return_msg(1, R_PAT));
	ft_putendl_fd(buffer, fd_out);
	free(buffer);
	return (0);
}
