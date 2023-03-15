/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flarcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:45:42 by flarcher          #+#    #+#             */
/*   Updated: 2023/03/15 14:01:45 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_signal_kill_child(void)
{
	while (g_lpid && g_lpid->pid > 0)
	{
		kill(g_lpid->pid, SIGKILL);
		ms_lpid_del_pid(g_lpid->pid);
	}
}

void	ms_signal_handle_sig(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGQUIT && g_lpid)
	{
		ms_signal_kill_child();
		if (!g_lpid)
			printf("Quit (core dumped)\n");
	}
	else if (signum == SIGINT)
	{
		if (g_lpid)
			ms_signal_kill_child();
		else
		{
			rl_replace_line("", 0);
			printf("\n");
			rl_on_new_line();
			rl_redisplay();
		}
	}
	return ;
}
