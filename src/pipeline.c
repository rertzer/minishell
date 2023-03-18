/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:08:17 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/18 12:23:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_pipeline_run(t_msdata *msdata);

int	ms_pipeline_start(t_msdata *msdata)
{
	int			ret;

	ret = ms_pipeline_run(msdata);
	ms_pipeline_clean(msdata);
	return (ret);
}

static int	ms_pipeline_run(t_msdata *msdata)
{
	int	ret;
	int	fd_out;

	if (msdata->cmd_nb == 1 && ms_builtin_itis(msdata->cmds[0].cmd_path))
	{
		msdata->cmds->cmd_nb = 0;
		fd_out = ms_output_openall(msdata->cmds);
		if (fd_out != -1)
		{
			ret = ms_builtin_run(msdata, msdata->cmds, fd_out);
			ms_msdata_close(fd_out);
		}
		ms_pipeline_clean(msdata);
		return (ret);
	}
	else
		return (pp_run_pipe(msdata));
}

void	ms_pipeline_clean(t_msdata *msdata)
{
	ms_command_clean(msdata);
	pp_run_close_pipes(msdata);
	free(msdata->pipefd);
	msdata->pipefd = NULL;
}
