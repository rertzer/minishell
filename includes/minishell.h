/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:09:37 by rertzer           #+#    #+#             */
/*   Updated: 2023/03/16 14:03:17 by rertzer          ###   ########.fr       */
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
# define DL_CHAR " \t$/"
# define LD_CHAR " \t$/\\"
# define CD_CHAR " \t/"

# define PROMPT "\001\e[1;32m\002Minishell: \001\e[0m\002"

# define DP fprintf(stderr, "%s %d\n", __FILE__, __LINE__);

# define R_NVI "not a valid identifier"
# define R_AMB "ambigous redirect"
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
# define R_NUM "numeric argument required"
# define R_SNP "string not in pwd"

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

typedef int		(*t_builtin_fun)(t_command *cmd, char ***envp, int fd_out);

extern t_lpid	*g_lpid;

/* ===================================================================== */
/*                            main and signals                           */
/* ===================================================================== */
/* lpid */
t_lpid	*ms_lpid_new(pid_t pid);
void	ms_lpid_add(t_lpid *new);
void	ms_lpid_add_back(t_lpid *new);
/* lpid del */
void	ms_lpid_clean(void);
void	ms_lpid_delone(t_lpid *lpid);
void	ms_lpid_del_pid(pid_t target);
/* signal */
void	ms_signal_kill_child(void);
void	ms_signal_handle_sig(int signum, siginfo_t *info, void *context);

/* ================================================================= */
/*                           Builtins                                */
/* ================================================================= */
/* builtin */
int		ms_builtin_itis(char *name);
int		ms_builtin_run(t_command *cmd, char ***envp, int fd_out, \
		int status);
/* cd */
int		ms_cd_run(t_command *cmd, char ***envp, int fd_out);
/* cd_utils */
char	*ms_cd_simplify(char **dirlst);
/* echo */
int		ms_echo_run(t_command *cmd, char ***envp, int fd_out);
/* env */
char	*ms_env_getvalue(char **envp, char *key);
int		ms_env_getindex(char **envp, char *key);
int		ms_env_run(t_command *cmd, char ***envp, int fd_out);
/* export */
int		ms_export_run(t_command *cmd, char ***envp, int fd_out);
int		ms_export_arg(char *arg, char ***envp);
/* pwd */
int		ms_pwd_run(t_command *cmd, char ***envp, int fd_out);
/* unset */
int		ms_unset_run(t_command *cmd, char ***envp, int fd_out);

/* ================================================================= */
/*                        parse and run                              */
/* ================================================================= */
/* args */
int		ms_args_add(t_command *cmd, char *line);
int		ms_args_getnb(t_command *cmd);
int		ms_args_insert(t_command *cmd, char *line);
/* args parse */
int		ms_args_parse(t_command *cmd);
/* atoi */
int		ms_atoi(const char *nptr, int *status);
/* backtrack */
int		ms_backtrack_backtrack(char prev, char *pattern, char *name);
/* char */
int		ms_char_isin(char c, char *special);
int		ms_char_nextexist(char *line);
int		ms_char_prevok(char *line, int i);
char	*ms_char_unprotect(char *line);
/* command */
int		ms_command_addback(t_command **start);
int		ms_command_clean(t_command **cmd);
void	ms_command_close(int fd);
/* dollar */
char	*ms_dollar_parse(char *line, char **envp, int status);
/* exit */
void	ms_exit_msg(t_pipeline *ppl, char ***envp, char *msg);
void	ms_exit_error(t_pipeline *ppl, char *msg, char ***envp);
void	ms_exit_child(char *path, char **args, char ***envp);
void	ms_exit_path(t_pipeline *ppl, char *msg, char ***envp);
void	ms_exit_exit(t_pipeline *ppl, char ***envp, char **args);
int		ms_exit_getstatus(char **args, int *status);
/* exit run */
int		ms_exit_run(t_command *cmd, char ***envp, int fd_out);
/* file */
int		ms_file_start(t_command *cmd);
/* file utils */
int		ms_file_chevron(t_command *cmd, int mode);
/* output */
int		ms_output_openall(t_command *cmd);
/* parsing */
int		ms_parsing_start(char *line, char ***envp, int status);
/* pipe */
int		ms_pipe_start(char *line, char ***envp, int status);
/* pipeline */
int		ms_pipeline_start(t_command *cmd_start, int cmd_nb, \
		char ***envp, int status);
void	ms_pipeline_clean(t_pipeline *ppl);
/* redirect */
char	*ms_redirect_start(char *word);
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
/* split */
char	**ms_split_protected(char const *s, char c);
/* tfile */
int		ms_tfile_addback(t_file **start, char *parsed, char mode);
int		ms_tfile_clean(t_file **file);
/* trim */
char	*ms_trim_trim(char *line);
/* utils */
int		ms_utils_spaceonly(char *str);
int		ms_utils_isonly(char *str, char c);
int		ms_utils_wordlen(char *str);
char	*ms_utils_strreplace(char *str, char *ins, int offset, int len);
int		ms_utils_insert(char *str, char ***table);
/* wildcard */
char	**ms_wildcard_start(char *line);
/* **********************************************************************/
/*                               pipex                                  */
/* **********************************************************************/
/* here doc */
int		pp_here_doc(t_pipeline *ppl, char *limiter, char ***envp);
/* check_cmd */
void	pp_check_cmd_path(t_pipeline *ppl, t_command *cmd, char ***envp);
/* Run */
int		pp_run_pipe(t_pipeline *ppl, char ***envp);
void	pp_run_close_pipes(t_pipeline *ppl);
int		pp_run_wait(void);
/* Open */
void	pp_open_in(t_pipeline *ppl, t_command *cmd, int i, char ***envp);
void	pp_open_out(t_pipeline *ppl, t_command *cmd, int i, char ***envp);
int		pp_open_flags(char mode);
/* Child */
void	pp_child_run(t_pipeline *ppl, t_command *cmd, char ***envp, int i);
/* Utils */
void	pp_nullfree(char **ptr);
int		pp_path_size(char const *s1, char const *s2);
char	*pp_pathjoin(char const *s1, char const *s2);
int		pp_duplicate(char const *src, char *dest, int shift);
#endif
