/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msdata.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:23:20 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 15:38:30 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_msdata_init(t_msdata *msdata)
{
	msdata->status = 0;
	msdata->cmd_nb = 0;
	msdata->cmds = NULL;
	msdata->pipefd = NULL;
	msdata->envp = NULL;
}

void	ms_msdata_clean(t_msdata *msdata)
{
	ms_pipeline_clean(msdata);
	ft_split_flush(msdata->envp);
	msdata->envp = NULL;
}
