/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:09:37 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/12 17:56:37 by rertzer          ###   ########.fr       */
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

# define FUN_TOP 8
# define SQ_CHAR " $*|<>\t"
# define DQ_CHAR " *|<>\t"
# define QT_CHAR "'\""
# define FL_CHAR " \t<>"
# define SP_CHAR " \t"

# define R_STR "string error"
# define R_SPL "split error"
# define R_MAL "malloc error"
# define R_PAT "path not found"
# define R_WRT "write error"
# define R_CMD "command not found"
# define R_FRK "fork error"
# define R_PIP "pipe error"
# define R_SYN "syntax error"
# define R_OPN "open error"
# define R_QUT "Q"

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

typedef struct s_pipeline
{
	int			cmd_nb;
	t_command	*cmds;
	int			(*pipefd)[2];
}				t_pipeline;

typedef struct s_lpid
{
	pid_t				pid;
	struct s_lpid		*next;
	struct s_lpid		*last;
}				t_lpid;

typedef struct s_term
{
	struct termios		interact_tio;
	struct termios		process_tio;
	int					tty_device;
}				t_term;

typedef int		(*t_builtin_fun)(t_command *cmd, char ***envp);

extern t_lpid	*g_lpid;

/* ===================================================================== */
/*                            main and signals                           */
/* ===================================================================== */
/* lpid */
t_lpid	*ms_lpid_new(pid_t pid);
void	ms_lpid_add(t_lpid *new);
void	ms_lpid_add_back(t_lpid *new);
/* lpid del */
void	ms_lpid_delone(t_lpid *lpid);
void	ms_lpid_del_pid(pid_t target);
/* minishell */
void	ms_set_sigaction(struct sigaction *sa);
int		ms_set_termios(struct termios *interact_tio,	\
		struct termios *process_tio);
void	shell_loop(t_term term, char ***envp, int *status);
/* signal */
void	ms_signal_kill_child(void);
void	ms_signal_handle_sig(int signum, siginfo_t *info, void *context);

/* ================================================================= */
/*                           Builtins                                */
/* ================================================================= */
/* builtin */
int		ms_builtin_itis(char *name);
int		ms_builtin_run(t_command *cmd, char ***envp);
/* cd */
int		ms_cd_setpath(char *key, char const *value, char ***envp);
char	*ms_cd_resolvepath(char *path, char *pwd);
int		ms_cd_run(t_command *cmd, char ***envp);
int		ms_cd_chdir(char *path, char *new_path);
/* cd_utils */
int		ms_cd_isdbldot(char *dir);
int		ms_cd_rmprev(char **dirlst, int current);
char	*ms_cd_recompose(char **dirlst);
char	*ms_cd_simplify(char **dirlst);
/* echo */
int		ms_echo_run(t_command *cmd, char ***envp);
/* env */
char	*ms_env_getvalue(char **envp, char *key);
int		ms_env_getindex(char **envp, char *key);
int		ms_env_valueindex(char *env, char *key);
int		ms_env_run(t_command *cmd, char ***envp);
/* export */
int		ms_export_run(t_command *cmd, char ***envp);
int		ms_export_arg(char *arg, char ***envp);
int		ms_export_set(char *arg, char **envp, int index);
/* pwd */
int		ms_pwd_run(t_command *cmd, char ***envp);
/* unset */
int		ms_unset_run(t_command *cmd, char ***envp);

/* ================================================================= */
/*                        parse and run                              */
/* ================================================================= */
/* args */
int		ms_args_add(t_command *cmd, char *line);
int		ms_args_getnb(t_command *cmd);
int		ms_args_parse(t_command *cmd);
int		ms_args_parseloop(t_command *cmd, int i, int start, int word);
int		ms_args_insert(t_command *cmd, char *line);
/* args utils */
int		ms_args_wildinsert(t_command *cmd, char *line, int start, int i);
int		ms_args_expinsert(t_command *cmd, char **expanded);
/* backtrack */
int		ms_backtrack_backtrack(char prev, char *pattern, char *name);
int		ms_backtrack_match(char prev, char pattern, char name);
int		ms_backtrack_iswildcard(char prev, char pattern);
/* char */
int		ms_char_isin(char c, char *special);
int		ms_char_nextexist(char *line);
int		ms_char_prevok(char *line, int i);
char	*ms_char_unprotect(char *line);
/* command */
void	ms_command_init(t_command *cmd);
int		ms_command_addback(t_command **start);
int		ms_command_clean(t_command **cmd);
void	ms_command_clean_one(t_command *cmd);
void	ms_command_close(int fd);
/* dollar */
char	*ms_dollar_parse(char *line, char **envp, int status);
char	*ms_dollar_getvalue(char *key, int status, char **envp);
int		ms_dollar_copykey(char **key, char **line, int i);
int		ms_dollar_replace(char **line, int i, char **envp, int status);
/* exit */
void	ms_exit_msg(t_pipeline *ppl, char ***envp, char *msg);
void	ms_exit_error(t_pipeline *ppl, char *msg);
int		ms_exit_run(t_command *cmd, char ***envp);
/* file */
int		ms_file_start(t_command *cmd);
int		ms_file_parse(t_command *cmd);
/* file utils */
void	ms_file_mode(char *path, char *mode, int *shift);
int		ms_file_wordend(char *line, int j);
t_file	**ms_file_adr(t_command *cmd, int mode);
int		ms_file_chevron(t_command *cmd, int mode);
/* parsing */
int		ms_parsing_start(char *line, char ***envp, int status);
int		ms_parsing_computelen(char *line);
void	ms_parsing_quote(char *line, char *new_line);
int		ms_parsing_toprotect(char quote, char c);
int		ms_parsing_isquote(char *line, char *quote);
/* pipe */
int		ms_pipe_start(char *line, char ***envp);
int		ms_pipe_cmdinit(t_command **cmd_start, char *line);
int		ms_pipe_split(t_command *cmd, int *cmd_nb);
int		ms_pipe_cut(t_command *cmd, char *line, int *start, int *i);
/* pipeline */
int		ms_pipeline_start(t_command *cmd_start, int cmd_nb, char ***envp);
void	ms_pipeline_init(t_pipeline *ppl, t_command *cmd_start, int cmd__nb);
void	ms_pipeline_clean(t_pipeline *ppl);
int		ms_pipeline_run(t_pipeline *ppl, char ***envp);
/* return */
int		ms_return_freeturn(char **ptr, int ret);
int		ms_return_msg(int ret, char *msg);
int		ms_return_error(int ret, char *msg);
/* return null */
char	*ms_return_null(char *msg);
char	*ms_return_nullerror(char *msg);
char	**ms_return_null2error(char *msg);
/* sort */
void	ms_sort_sort(char **tosort);
void	ms_sort_loop(char **tosort, int len);
int		ms_sort_swap(char **tosort, int i);
/* split */
char	**ms_split_protected(char const *s, char c);
/* tfile */
int		ms_tfile_addback(t_file **start, char *parsed, char mode);
int		ms_tfile_clean(t_file **file);
/* trim */
char	*ms_trim_trim(char *line);
/* utils */
int		ms_utils_spaceonly(char *str);
int		ms_utils_wordlen(char *str);
char	*ms_utils_strreplace(char *str, char *ins, int offset, int len);
int		ms_utils_insert(char *str, char ***table);
/* wildcard */
char	**ms_wildcard_start(char *line);
int		mw_wildcard_export(struct dirent *entry, char *pattern, \
		char ***expanded);
char	**ms_wildcard_expand(DIR *dd, char *line);
char	**ms_wildcard_returnclean(char *pattern, char **expanded);
/* **********************************************************************/
/*                               pipex                                  */
/* **********************************************************************/
/* here doc */
int		pp_here_doc(t_pipeline *ppl, char *limiter);
char	*pp_here_line(t_pipeline *ppl, char *limiter, char *line, int *pipefd);
/* check_cmd */
void	pp_check_cmd_path(t_pipeline *ppl, t_command *cmd, char ***envp);
void	pp_check_path(t_pipeline *ppl, t_command *cmd,	\
		char **paths, char ***envp);
void	pp_check_exit(t_pipeline *ppl, char **paths, char ***envp);
/* Run */
int		pp_run_pipe(t_pipeline *ppl, char ***envp);
void	pp_run_close_pipes(t_pipeline *ppl);
int		pp_run_wait(void);
int		pp_run_make_pipes(t_pipeline *ppl);
int		pp_run_fork(t_pipeline *ppl, char ***envp);
/* Open */
int		pp_open_file(t_pipeline *pp, t_file *file, char ***envp);
int		pp_open_flags(char mode, t_pipeline *ppl, char ***envp);
void	pp_open_in(t_pipeline *ppl, t_command *cmd, int i, char ***envp);
void	pp_open_out(t_pipeline *ppl, t_command *cmd, int i, char ***envp);
/* Child */
void	pp_child_run(t_pipeline *ppl, t_command *cmd, char ***envp, int i);
void	pp_child_dupfd(t_pipeline *ppl, t_command *cmd);
void	pp_child_exec(t_pipeline *ppl, t_command *cmd, char ***envp);
/* Utils */
void	pp_nullfree(char **ptr);
int		pp_path_size(char const *s1, char const *s2);
char	*pp_pathjoin(char const *s1, char const *s2);
int		pp_duplicate(char const *src, char *dest, int shift);
/* *************************************************************************/
/*                            printf                                       */
/* *************************************************************************/
/* ft_itoa */
char	*ft_itoa(int nb);
#endif
