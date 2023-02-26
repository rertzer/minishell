/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flarcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:05:02 by flarcher          #+#    #+#             */
/*   Updated: 2023/02/22 11:05:04 by flarcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lpid	*g_lpid = NULL;

void	ms_minishell_handle_sig(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGQUIT)
	{
		if (g_lpid && g_lpid->pid != getpid())
		{
			while (g_lpid && g_lpid->pid > 0)
			{
				kill(g_lpid->pid, SIGKILL);
				ms_lpid_del_pid(g_lpid->pid);
			}
			if (!g_lpid)
				printf("Quit (core dumped)\n");
		}
		else
			printf("\e[1;32mMinishell: \e[0m");
	}
	else if (signum == SIGINT)
	{
		if (g_lpid)
		{
			while (g_lpid && g_lpid->pid > 0)
			{
				kill(g_lpid->pid, SIGKILL);
				ms_lpid_del_pid(g_lpid->pid);
			}
		}
		else
			printf("\n\e[1;32mMinishell: \e[0m");
	}
	return ;
}

int	ms_minishell_process_exemple(char *line)
{
	int	i;

	i = 0;
	if (line[0] == 'e')
		exit(0);
	while (i < 10)
	{
		printf("CHILD [%d][%d] IS SLEEPING\n", g_lpid->pid, getpid());
		sleep(1);
		i += 2;
	}
	printf("CHILD [%d][%d] IS AWAKE\n", g_lpid->pid, getpid());
	free(line);
	return (1);
}

static	int	ms_minishell_temporary_start(char *line)
{
	int	status;

	if (line[0] == 'e' && line[1] == 'x' && line[2] == 'i' && line[3] == 't')
	{
		free(line);
		exit(0);
	}
	g_lpid = ms_lpid_new(fork());
	if (g_lpid->pid != 0)
		ms_lpid_add(ms_lpid_new(fork()));
	if (g_lpid->pid == 0)
		exit (ms_minishell_process_exemple(line));
	else if (g_lpid)
	{
		while (g_lpid && g_lpid->pid > 0)
		{
			waitpid(g_lpid->pid, &status, 0);
			if (g_lpid)
				ms_lpid_del_pid(g_lpid->pid);
		}
	}
	ms_lpid_print();
	free(line);
	return (1);
}

int	main(void)
{
	char				*line;
	char				*prompt;
	struct sigaction	sa;

	prompt = "\e[1;32mMinishell: \e[0m";
	sa.sa_sigaction = ms_minishell_handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		line = readline(prompt);
		if (!line)
			continue ;
		add_history(line);
		rl_on_new_line();
		ms_minishell_temporary_start(line);
	}
	return (1);
}
