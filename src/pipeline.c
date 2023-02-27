/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:08:17 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/27 15:20:59 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipeline_run(t_command *cmd_start, int cmd_nb, char **envp)
{
	t_pipeline	ppl;

	//ms_pipex_print(cmd_start, cmd_nb);
	ppl.cmd_nb = cmd_nb;
	ppl.cmds = cmd_start;
	ppl.pipefd = NULL;
	return (ms_pipex_run(&ppl, envp));
}