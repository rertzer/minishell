/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:41:14 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 15:16:17 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd_run(t_command *cmd, char ***envp)
{
	char *buffer;

	(void)cmd;
	buffer = ms_env_getvalue(*envp, "PWD");
	if (buffer == NULL)
		return (ms_return_msg(1, R_PAT));
	ft_putendl_fd(buffer, 1);
	free(buffer);
	return (0);
}
