/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:09:37 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/06 11:05:29 by rertzer          ###   ########.fr       */
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

# define DP fprintf(stderr, "%s %d\n", __FILE__, __LINE__);
# define FUN_TOP 6
# define SQ_CHAR " $*|<>\t"
# define DQ_CHAR " *|<>\t"
# define QT_CHAR "'\""
# define FL_CHAR " \t<>"
# define SP_CHAR " \t"

typedef struct s_file
{
	char			*name;
	char			mode;
	struct s_file	*next;
}				t_file;

typedef struct s_command
{
	int					fd_in;
	int					fd_out;
	struct s_file		*infile;
	struct s_file		*outfile;
	char				*cmd_path;
	char				**args;
	int					cmd_nb;
	struct s_command	*next;
}				t_command;

typedef struct	s_pipeline
{
	int			cmd_nb;
	t_command	*cmds;
	int			(*pipefd)[2];
}				t_pipeline;

typedef struct	s_lpid
{
	pid_t				pid;
	struct s_lpid		*next;
	struct s_lpid		*last;
}				t_lpid;


typedef	int (*builtin_fun)(t_command *cmd, char ***envp);

extern t_lpid *g_lpid;

/* parsing */
int		ms_parsing_start(char *line, char ***envp);
void	ms_parsing_quote(char *line, char *new_line);
int		ms_parsing_isquote(char *line, char *quote);
/* char */
int		ms_char_isin(char c, char *special);
int		ms_char_nextexist(char *line);
int		ms_char_prevok(char *line, int i);
char	*ms_char_unprotect(char *line);
/* file */
int		ms_file_start(t_command *cmd);
int		ms_file_parse(t_command *cmd);
/* file utils */
void	ms_file_mode(char *path, char *mode, int *shift);
int		ms_file_wordend(char *line, int j);
t_file	**ms_file_adr(t_command *cmd, int mode);
int		ms_file_chevron(t_command *cmd, int mode);
/* args */
int		ms_args_add(t_command *cmd, char *line);
int		ms_args_getnb(t_command *cmd);
int		ms_args_parse(t_command *cmd);
int		ms_args_parseloop(t_command *cmd, int i, int start, int word);
int		ms_args_insert(t_command *cmd, char *line);
/* builtin */
int		ms_builtin_itis(char *name);
int		ms_builtin_run(t_pipeline *ppl, t_command *cmd, char ***envp);
/* cd */
int		ms_cd_setpath(char *key, char *value, char ***envp);
char	*ms_cd_resolvepath(char *path, char *pwd);
int		ms_cd_run(t_command *cmd, char ***envp);
/* cd_utils */
int		ms_cd_isdbldot(char *dir);
int		ms_cd_rmprev(char **dirlst, int current);
char	*ms_cd_recompose(char **dirlst);
char	*ms_cd_simplify(char **dirlst);
/* command */
void	ms_command_init(t_command *cmd);
int		ms_command_addback(t_command **start);
int		ms_command_clean(t_command **cmd);
void	ms_command_clean_one(t_command *cmd);
void	ms_command_close(int fd);
/* dollar */
char	*ms_dollar_parse(char *line, char **envp);
int		ms_dollar_replace(char **line, int i, char **envp);
/* echo */
int		ms_echo_run(t_command *cmd, char ***envp);
/* env */
char	*ms_env_getvalue(char **envp, char *key);
int		ms_env_getindex(char **envp, char *key);
int		ms_env_valueindex(char *env, char *key);
int		ms_env_run(t_command *cmd, char ***envp);
/* exit */
void	ms_exit_msg(t_pipeline *ppl, char *msg);
void	ms_exit_error(t_pipeline *ppl, char *msg);
/* export */
int		ms_export_run(t_command *cmd, char ***envp);
void	ms_export_arg(char *arg, char ***envp);
void	ms_export_new(char *arg, char ***envp);
void	ms_export_set(char *arg, char **envp, int index);
/* lpid */
t_lpid	*ms_lpid_new(pid_t pid);
void	ms_lpid_add(t_lpid *new);
void	ms_lpid_delone(t_lpid *lpid);
void	ms_lpid_del_pid(pid_t target);
void	ms_lpid_print(void);
/* minishell */
void	ms_minishell_handle_sig(int signum, siginfo_t *info, void *context);
int 	ms_set_termios(struct termios	*interact_tio, struct termios	*process_tio);
/* pipe */
int		ms_pipe_start(char *line, char ***envp);
int		ms_pipe_split(t_command *cmd, int *cmd_nb);
/* pipeline */
int		ms_pipeline_run(t_command *cmd_start, int cmd_nb, char ***envp);
void	ms_pipeline_clean(t_pipeline *ppl);
int		ms_pipex_print(t_command *cmd_start, int cmd_nb);// remove for submission 
/* pipex run */
int		ms_pipex_run(t_pipeline *ppl, char ***envp);
/* pwd */
int		ms_pwd_run(t_command *cmd, char ***envp);
/* return */
int		ms_return_freeturn(char **ptr, int ret);
int		ms_return_msg(int ret, char *msg);
int		ms_return_error(int ret, char *msg);
/* signal */
void	ms_signal_kill_child(void);
void	ms_signal_handle_sig(int signum, siginfo_t *info, void *context);
/* tfile */
int		ms_tfile_addback(t_file **start, char *parsed, char mode);
int		ms_tfile_clean(t_file **file);
/* trim */
char	*ms_trim_trim(char *line);
/* utils */
int		ms_utils_spaceonly(char *str);
char	*ms_utils_trim(char *str);
int		ms_utils_wordlen(char *str);
char	*ms_utils_strreplace(char *str, char *ins, int offset, int len);

/* **********************************************************************/
/*                               pipex                                  */
/* **********************************************************************/
/* here doc */
int		pp_here_doc(t_pipeline *ppl, char *limiter);
char	*pp_here_line(t_pipeline *ppl, char *limiter, char *line, int *pipefd);
/* check_cmd */
void	pp_check_cmd_path(t_pipeline *ppl, t_command *cmd);
void	pp_check_path(t_pipeline *ppl, t_command *cmd, char **paths);
/* Run */
int		pp_run_pipe(t_pipeline *ppl, char ***envp);
void	pp_run_close_pipes(t_pipeline *ppl);
void	pp_run_wait(t_pipeline *ppl);
int		pp_run_make_pipes(t_pipeline *ppl);
int		pp_run_fork(t_pipeline *ppl, char ***envp);
/* Child */
int		pp_open_file(t_pipeline *pp, t_file *file);
void	pp_open_in(t_pipeline *ppl, t_command *cmd, int i);
void	pp_open_out(t_pipeline *ppl, t_command *cmd, int i);
void	pp_run_child(t_pipeline *ppl, t_command *cmd, char ***envp, int i);
/* Utils */
void	pp_nullfree(char **ptr);
int		pp_path_size(char const *s1, char const *s2);
char	*pp_pathjoin(char const *s1, char const *s2);
#endif
