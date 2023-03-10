/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexrun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:22:45 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 11:58:48 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipex_run(t_pipeline *ppl, char ***envp)
{
	int	ret;

	if (ppl->cmd_nb == 1 && ms_builtin_itis(ppl->cmds[0].cmd_path))
	{
		ppl->cmds->cmd_nb = 0;
		ret = ms_builtin_run(ppl->cmds, envp);
		ms_pipeline_clean(ppl);
		return (ret);
	}
	else
		return (pp_run_pipe(ppl, envp));
}
