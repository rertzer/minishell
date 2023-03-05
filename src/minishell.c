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

int	ms_set_termios(struct termios *interact_tio, struct termios *process_tio)
{
	int	tty_device;

	tty_device = ttyslot();
	if (!isatty(tty_device))
		return (-1);
	if (tcgetattr(tty_device, interact_tio) != 0)
		return (-1);
	if (tcgetattr(tty_device, process_tio) != 0)
		return (-1);
	interact_tio->c_cc[VQUIT] = 0;
	return (1);
}

void	ms_set_sigaction(struct sigaction *sa)
{
	sa->sa_sigaction = ms_signal_handle_sig;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

int	main(void)
{
	char				*line;
	int					tty_device;
	struct sigaction	sa;
	struct termios		interact_tio;
	struct termios		process_tio;

	tty_device = ms_set_termios(&interact_tio, &process_tio);
	if (tty_device < 0)
		return (-1);
	ms_set_sigaction(&sa);
	while (1)
	{
		tcsetattr(tty_device, TCSANOW, &interact_tio);
		line = readline("\e[1;32mMinishell: \e[0m");
		if (!line)
			break ;
		add_history(line);
		rl_on_new_line();
		tcsetattr(tty_device, TCSANOW, &process_tio);
		ms_minishell_temporary_start(line);
	}
	tcsetattr(tty_device, TCSANOW, &process_tio);
	return (1);
}
