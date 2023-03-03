/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flarcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:45:42 by flarcher          #+#    #+#             */
/*   Updated: 2023/03/03 17:45:43 by flarcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (signum == SIGQUIT && g_lpid && g_lpid->pid != getpid())
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
			printf("\n\e[1;32mMinishell: \e[0m");
	}
	return ;
}
