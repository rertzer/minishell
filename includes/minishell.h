/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:09:37 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/22 13:45:20 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>

# define RAW 0
# define SQT 1
# define DQT 2

typedef struct s_line
{
	int				kind;
	char			*line;
	struct s_line	*next;
}				t_line;		

typedef struct s_command
{
	char	*inflile_name;
	char	*outfile_name;
	char	*limiter;
	char	*cmd_path;
	char	**args;
	int		cmd_nb;
	int		(*pipefd)[2];
}				t_command;

/* main */
/* parsing */
int	ms_parsing_start(char *line);

#endif
