/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flarcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:05:02 by flarcher          #+#    #+#             */
/*   Updated: 2023/03/13 10:09:27 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lpid	*g_lpid = NULL;

static int	ms_set_termios(struct termios *interact_tio,	\
							struct termios *process_tio);
static void	ms_set_sigaction(struct sigaction *sa);
static void	shell_loop(t_term term, char ***envp, int *status);

int	main(int argc, char **argv, char **old_envp)
{
	int					status;
	char				**envp;
	t_term				term;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	status = 0;
	term.tty_device = ms_set_termios(&term.interact_tio, &term.process_tio);
	envp = ft_2dstrdup(old_envp);
	ms_set_sigaction(&sa);
	while (1)
		shell_loop(term, &envp, &status);
	tcsetattr(term.tty_device, TCSANOW, &term.process_tio);
	return (1);
}

static int	ms_set_termios(struct termios *interact_tio,	\
							struct termios *process_tio)
{
	int	tty_device;

	tty_device = ttyslot();
	if (!isatty(tty_device))
		exit (ms_return_msg(-1, "ttyslot error"));
	if (tcgetattr(tty_device, interact_tio) != 0)
		exit (ms_return_msg(-1, "tcgetattr error"));
	if (tcgetattr(tty_device, process_tio) != 0)
		exit (ms_return_msg(-1, "tcgetattr error"));
	interact_tio->c_cc[VQUIT] = 0;
	return (tty_device);
}

static void	ms_set_sigaction(struct sigaction *sa)
{
	sa->sa_sigaction = ms_signal_handle_sig;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

static void	shell_loop(t_term term, char ***envp, int *status)
{	
	char	*line;

	line = NULL;
	tcsetattr(term.tty_device, TCSANOW, &term.interact_tio);
	line = readline(PROMPT);
	if (!line)
		ms_exit_run(NULL, envp);
	add_history(line);
	tcsetattr(term.tty_device, TCSANOW, &term.process_tio);
	ms_parsing_start(line, envp, *status);
	*status = pp_run_wait();
}
