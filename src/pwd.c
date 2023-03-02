/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:41:14 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/02 10:19:41 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd_run(t_command *cmd, char ***envp)
{
	char *buffer;

	(void)cmd;
	(void)envp;
	errno = 0;
	buffer = getcwd(NULL, 0);
	if (buffer == NULL)
		return (ms_return_error(errno, "pwd"));
	ft_putendl_fd(buffer, 1);
	free(buffer);
	return (0);
}
