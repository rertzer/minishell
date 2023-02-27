/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:52:18 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/27 14:30:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_itis(char *name)
{
	(void)name;
	return (0);
}

int	ms_builtin_run(t_command *cmd, char **envp)
{
	(void)cmd;
	(void)envp;
	return (0);
}
