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
pid_t cpid;

void	ms_minishell_handle_sig(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGQUIT)
	{
		if (cpid > 0)
		{
			kill(cpid, SIGKILL);
			printf("Quit (core dumped)\n");
			exit(0);
		}
		else
			rl_redisplay();
	}
	else if (signum == SIGINT)
	{
		if (cpid > 0)
			kill(cpid, SIGKILL);
		else{
			printf("\n\e[1;32mMinishell: \e[0m");
			rl_redisplay();
		}
	}
	return ;
}

static int	ms_minishell_start(char *line)
{
	int i =0;
	if (line[0]=='e')
		exit (0);
	while (i < 10)
	{
		printf("CHILD [%d] IS SLEEPING\n", (int)cpid);
		sleep(2);
		i+=2;
	}
	printf("CHILD [%d] IS AWAKE\n", cpid);
	free(line);
	return (1);
}

//SIGINT -> kill line process
//sig

int main(void)
{
	char *line;
	char *prompt = "\e[1;32mMinishell: \e[0m";
	struct sigaction 	sa;
	//struct termios		*termios_p;
	int 				status;

	sa.sa_sigaction = ms_minishell_handle_sig;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		line = readline(prompt);
		if (!line)
			continue;
		add_history(line);
	//	tcgetattr(0, termios_p);
		rl_on_new_line();
		cpid = fork();
		if (cpid == -1)
		{
			perror("fork");
			exit(1);
		}
		if (cpid==0)
			return (ms_minishell_start(line));
		else
		{
			printf("wait child [%d]\n", cpid);
			waitpid(cpid, &status, 0);
			cpid = 0;
		}
		free (line);
	}
	return (1);
}