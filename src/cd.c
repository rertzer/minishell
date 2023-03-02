/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:19:46 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/02 10:19:29 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_cd_run(t_command *cmd, char ***envp)
{
	(void)envp;
	errno = 0;
	if (chdir(cmd->args[1]) == -1)
		ms_return_error(errno, "cd");
	// on peut encore gerer le tiret
	// variables d'env
	return (0);
}
