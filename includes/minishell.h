/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:09:37 by rertzer           #+#    #+#             */
/*   Updated: 2023/02/23 18:03:58 by rertzer          ###   ########.fr       */
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

# include "libft.h"

#define DP fprintf(stderr, "%s %d\n", __FILE__, __LINE__);

typedef struct s_line
{
	char			quote;
	char			*line;
	struct s_line	*next;
}				t_line;		

typedef struct s_command
{
	t_line			*line;
	char			*inflile_name;
	char			*outfile_name;
	char			*limiter;
	char			*cmd_path;
	char			**args;
	int				cmd_nb;
	int				(*pipefd)[2];
	struct s_line	next;
}				t_command;

/* minishell */
/* dollar */
int		ms_dollar_parse(t_line *to_parse, char **envp);
int		ms_dollar_parseline(t_line *to_parse, char **envp);
int		ms_dollar_replace(t_line *to_parse, int i, char **envp);
/* env */
char	*ms_env_getvalue(char **envp, char *key);
int		ms_env_valueindex(char *env, char *key);
/* line */
int		ms_line_addback(t_line **first, char quote, char *str);
int		ms_line_addin(t_line *prev, char *str);
char	*ms_line_extractnext(t_line *prev);
t_line	*ms_line_last(t_line *first);
void	ms_line_clean(t_line *first);
/* parsing */
int	ms_parsing_start(char *line, char **envp);
int	ms_parsing_quote(t_line *to_parse);
int	ms_parsing_sec_quote(t_line *to_parse, int i);
int	ms_parsing_print(t_line *line);
/* pipe */
int	ms_pipe_start(t_line *to_pipe);
/* split */
int	ms_split_split(t_line *to_parse, int i, int j);
int	ms_split_middle(t_line *to_parse, int i, int j);
int	ms_split_beggin(t_line *to_parse, int i, int j);
/* utils */
int		ms_utils_spaceonly(char *str);
char	*ms_utils_trim(char *str);
int		ms_utils_wordlen(char *str);
char	*ms_utils_strreplace(char *str, char *ins, int offset, int len);
#endif
