/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:08:17 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 11:48:50 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_pipeline_run(t_pipeline *ppl, char ***envp, int status);
static void	ms_pipeline_init(t_pipeline *ppl, t_command *cmd_start, int cmd_nb);

int	ms_pipeline_start(t_command *cmd_start, int cmd_nb, char ***envp, \
		int status)
{
	t_pipeline	ppl;
	int			ret;

	ms_pipeline_init(&ppl, cmd_start, cmd_nb);
	ret = ms_pipeline_run(&ppl, envp, status);
	ms_pipeline_clean(&ppl);
	return (ret);
}

static void	ms_pipeline_init(t_pipeline *ppl, t_command *cmd_start, int cmd_nb)
{
	ppl->cmd_nb = cmd_nb;
	ppl->cmds = cmd_start;
	ppl->pipefd = NULL;
}

static int	ms_pipeline_run(t_pipeline *ppl, char ***envp, int status)
{
	int	ret;
	int	fd_out;

	if (ppl->cmd_nb == 1 && ms_builtin_itis(ppl->cmds[0].cmd_path))
	{
		ppl->cmds->cmd_nb = 0;
		fd_out = ms_output_openall(ppl->cmds);
		if (fd_out != -1)
		{
			ret = ms_builtin_run(ppl->cmds, envp, fd_out, status);
			ms_command_close(fd_out);
		}
		ms_pipeline_clean(ppl);
		return (ret);
	}
	else
		return (pp_run_pipe(ppl, envp));
}

void	ms_pipeline_clean(t_pipeline *ppl)
{
	ms_command_clean(&ppl->cmds);
	pp_run_close_pipes(ppl);
	free(ppl->pipefd);
	ppl->pipefd = NULL;
}
