/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flarcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:45:42 by flarcher          #+#    #+#             */
/*   Updated: 2023/03/26 18:36:44 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_signal_kill_child(int signum)
{
	while (g_lpid && g_lpid->pid > 0)
	{
		kill(g_lpid->pid, signum);
		ms_lpid_del_pid(g_lpid->pid);
	}
}

void	ms_signal_handle_sig(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGQUIT && g_lpid)
	{
		ms_signal_kill_child(SIGQUIT);
		ft_putendl_fd("Quit (core dumped)", 2);
		rl_on_new_line();
	}
	else if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		if (g_lpid)
			ms_signal_kill_child(SIGINT);
		else
		{
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	return ;
}
