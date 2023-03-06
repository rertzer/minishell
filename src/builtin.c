/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:52:18 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 14:28:17 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_builtin_itis(char *name)
{
	int		i;
	char	*fun_names[FUN_TOP];

	if (name == NULL)
		return (0);
	fun_names[0] = "";
	fun_names[1] = "echo";
	fun_names[2] = "cd";
	fun_names[3] = "pwd";
	fun_names[4] = "env";
	fun_names[5] = "export";
	fun_names[6] = "unset";
	fun_names[7] = "exit";
	i = 0;
	while (++i < FUN_TOP)
	{
		if (ft_strcmp(name, fun_names[i]) == 0)
			return (i);
	}
	return (0);
}

int	ms_builtin_run(t_command *cmd, char ***envp)
{
	int			fun_index;
	builtin_fun	fun_exec[FUN_TOP];

	fun_exec[0] = NULL;
	fun_exec[1] = ms_echo_run;
	fun_exec[2] = ms_cd_run;
	fun_exec[3] = ms_pwd_run;
	fun_exec[4] = ms_env_run;
	fun_exec[5] = ms_export_run;
	fun_exec[6] = ms_unset_run;
	fun_exec[7] = ms_exit_run;
	fun_index = ms_builtin_itis(cmd->cmd_path);
	if (fun_index)
		return (fun_exec[fun_index](cmd, envp));
	return (1);
}
