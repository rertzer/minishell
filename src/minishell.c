/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flarcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:05:02 by flarcher          #+#    #+#             */
/*   Updated: 2023/03/19 13:59:28 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lpid	*g_lpid = NULL;

static int	ms_set_termios(struct termios *interact_tio,	\
							struct termios *process_tio);
static void	ms_set_sigaction(struct sigaction *sa);
static void	shell_loop(t_msdata *msdata, t_term term);

int	main(int argc, char **argv, char **old_envp)
{
	t_msdata			msdata;
	t_term				term;
	struct sigaction	sa;

	(void)argc;
	(void)argv;
	ms_msdata_init(&msdata);
	term.tty_device = ms_set_termios(&term.interact_tio, &term.process_tio);
	msdata.envp = ft_2dstrdup(old_envp);
	ms_set_sigaction(&sa);
	while (1)
		shell_loop(&msdata, term);
	tcsetattr(term.tty_device, TCSANOW, &term.process_tio);
	return (1);
}

static int	ms_set_termios(struct termios *interact_tio,	\
							struct termios *process_tio)
{
	int	tty_device;

	tty_device = ttyslot();
	if (!isatty(tty_device))
		exit (ms_return_msg(-1, NULL, R_TTY));
	if (tcgetattr(tty_device, interact_tio) != 0)
		exit (ms_return_msg(-1, NULL, R_TCG));
	if (tcgetattr(tty_device, process_tio) != 0)
		exit (ms_return_msg(-1, NULL, R_TCG));
	process_tio->c_cc[VQUIT] = 28;
	interact_tio->c_cc[VQUIT] = 0;
	return (tty_device);
}

static void	ms_set_sigaction(struct sigaction *sa)
{
	sa->sa_sigaction = ms_signal_handle_sig;
	sa->sa_flags = SA_RESTART;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGINT, sa, NULL);
	sigaction(SIGQUIT, sa, NULL);
}

static void	shell_loop(t_msdata *msdata, t_term term)
{	
	char	*line;

	line = NULL;
	tcsetattr(term.tty_device, TCSANOW, &term.interact_tio);
	line = readline(PROMPT);
	tcsetattr(term.tty_device, TCSANOW, &term.process_tio);
	if (!line)
		ms_exit_run(msdata, NULL, 2);
	add_history(line);
	ms_parsing_start(msdata, line);
	msdata->status = pp_run_wait();
}
