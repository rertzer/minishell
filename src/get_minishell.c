/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flarcher <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:05:02 by flarcher          #+#    #+#             */
/*   Updated: 2023/03/20 14:46:41 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lpid	*g_lpid = NULL;

static int	ms_set_termios(struct termios *interact_tio,	\
							struct termios *process_tio);
static void	ms_set_sigaction(struct sigaction *sa);
static void	shell_loop(t_msdata *msdata, t_term term, int fd);

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
	int fd = open("mini_test_list", O_RDONLY);
	if (fd < 0) return (1);
	while (1)
		shell_loop(&msdata, term, fd);
	close(fd);
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

static void trim_eol(char *line)
{
	for (int i = 0 ; line[i] ; i++)
	{
		if (line[i] == '\n')
			line[i] = '\0';
	}
}

static void	shell_loop(t_msdata *msdata, t_term term, int fd)
{	
	char	*line;

	line = NULL;
	tcsetattr(term.tty_device, TCSANOW, &term.interact_tio);
	//line = readline(PROMPT);
	line = get_next_line(fd);
	if (!line)
	{
		fprintf(stderr, "This is the end, my friend\n");
		free(line);
		ms_exit_run(msdata, NULL, 2);
	}
	trim_eol(line);
	//add_history(line);
	tcsetattr(term.tty_device, TCSANOW, &term.process_tio);
	ms_parsing_start(msdata, line);
	msdata->status = pp_run_wait();
	free(line);
	sleep(2);
}
