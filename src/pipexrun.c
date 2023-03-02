/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexrun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:22:45 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/02 10:23:51 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pipex_run(t_pipeline *ppl, char ***envp)
{
	if (ppl->cmd_nb == 1 && ms_builtin_itis(ppl->cmds->cmd_path))
		return (ms_builtin_run(ppl, ppl->cmds, envp));
	else
		return (pp_run_pipe(ppl, envp));
}
