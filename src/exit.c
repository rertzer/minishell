/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:55:38 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/01 16:00:38 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit_msg(t_pipeline *ppl, char *msg)
{
	ms_pipeline_clean(ppl);
	if (msg)
	{
		ft_putendl_fd(msg, 2);
		exit(1);
	}
	exit(0);
}

void	ms_exit_error(t_pipeline *ppl, char *msg)
{
	perror(msg);
	ms_pipeline_clean(ppl);
	exit(1);
}
