/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:08:17 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 15:04:58 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipeline_run(t_command *cmd_start, int cmd_nb, char ***envp)
{
	t_pipeline	ppl;
	int			ret;

	ppl.cmd_nb = cmd_nb;
	ppl.cmds = cmd_start;
	ppl.pipefd = NULL;
	ret = ms_pipex_run(&ppl, envp);
	ms_pipeline_clean(&ppl);
	return (ret);
}

void	ms_pipeline_clean(t_pipeline *ppl)
{
	ms_command_clean(&ppl->cmds);
	pp_run_close_pipes(ppl);
	free(ppl->pipefd);
	ppl->pipefd = NULL;
}
